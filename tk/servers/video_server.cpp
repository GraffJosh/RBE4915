
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <future>
#include <iostream>
#include <pthread.h>
#include <arm_aruco.h>
#include <arm_april.h>
#include <arm_control.h>
#include "server.h"
#include "aruco_camera.h"
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

using namespace udp_client_server;
using namespace cv;
using namespace std;
pthread_t receive_thread;
cv::Mat received_frame;
Point2d clicked_point;
bool clicked = false;
udp_client_server::udp_server* image_server;
void window_callback(int event, int x, int y, int flags, void* userdata);

void* get_images(void*)
{

  image_server->receive_image(received_frame.rows, received_frame.cols);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  int received_frames = 0;
  int num_markers = 0;

  VideoWriter outputVideo;
  if(argc>1) { string argument;
    argument.append(argv[argc-1]);
    outputVideo.open("output"+argument, 0, 10, Size(IMAGE_WIDTH,IMAGE_HEIGHT), true);  }

  received_frame = Mat::zeros(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC3);
  image_server = new udp_client_server::udp_server("192.168.10.8",1234);
  pthread_create(&receive_thread, NULL, get_images,NULL);

  Mat proc_frame = Mat::zeros(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC3);  //unpainted frame for processing
  Mat draw_frame = Mat::zeros(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC3);  //painted frame for people
  Arm_april left_arm(11,proc_frame);              //tracking and arm management
  Arm_Control left_control(1,"192.168.10.64",5005);

  Aruco_Camera input_cam;
  input_cam.readFromXMLFile("Camera_Calib.yml");
  input_cam.resize(received_frame.size());
  input_cam.add_points(Point3f(0,-400,-1250),Point2f(95,290));
  input_cam.add_points(Point3f(0,-350,-1250),Point2f(108,256));
  input_cam.add_points(Point3f(0,-300,-1250),Point2f(110,226));
  input_cam.add_points(Point3f(0,-250,-1250),Point2f(110,197));
  input_cam.add_points(Point3f(150,-300,-1250),Point2f(195,226));
  input_cam.add_points(Point3f(200,-300,-1250),Point2f(221,230));
  input_cam.add_points(Point3f(250,-300,-1250),Point2f(247,235));
  input_cam.add_points(Point3f(300,-300,-1250),Point2f(277,244));
  input_cam.add_points(Point3f(350,-300,-1250),Point2f(311,245));
  input_cam.add_points(Point3f(400,-300,-1250),Point2f(345,230));
  input_cam.add_points(Point3f(400,-500,-1250),Point2f(348,355));
  input_cam.add_points(Point3f(300,-500,-1250),Point2f(284,354 ));
  // {{110,0}, {195,150} ,{221,200} ,{247,250} ,{277,300} ,{311,350} ,{345,400}}  // input_cam.add_points(Point3f(0,-600,-1931),Point2f(209,338 ));
  // {{290,-400 },{256,-350 },{197,-250 },{235,-300 },{355,-500 }}// input_cam.add_points(Point3f(200,-600,-1931),Point2f(287,337 ));
  // input_cam.add_points(Point3f(400,-600,-1931),Point2f(368,339 ));
  // input_cam.add_points(Point3f(400,0,-1931),Point2f(362,96 ));
  // input_cam.add_points(Point3f(0,0,-1931),Point2f(204,128 ));
  input_cam.calibrate();


  namedWindow("draw_window", 1);
  setMouseCallback("draw_window", window_callback, NULL);

  cout<<left_control.send_point(100,500,-300,200)<<'\n';

  while (1) {

      switch (image_server->read_image(&received_frame))
      {
        case 0:
          // cv::imshow("frame",received_frame);
          if (outputVideo.isOpened())
          { outputVideo <<received_frame;}
          undistort(received_frame,proc_frame, input_cam.CameraMatrix,input_cam.Distorsion);
          // received_frame.copyTo(proc_frame);
          received_frames++;
          break;
        case 1:
          // cv::imshow("frame",received_frame);
          break;
        case -2:
          usleep(100);
          continue;
      }


    if(received_frames >0 )
    {
          num_markers = left_arm.detect_arm();
          proc_frame.copyTo(draw_frame);
          left_arm.draw_markers(draw_frame);
          left_arm.draw_box(draw_frame);
          cv::imshow("draw_window",draw_frame);
    }

      if(clicked)
      {
        std::cout << "arm seen: "<<left_arm.get_position()<<'\n' ;
        std::cout << "arm_actual: " << left_control.get_position()<< '\n';
        Point3d transformed = input_cam.transformto_real(clicked_point);
        std::cout << "transformed: " << transformed<<'\n';
        std::cout << "clicked: " <<clicked_point<< '\n';
        clicked = false;
        left_control.send_point(100,transformed.x,transformed.y,200);
      }
      cv::waitKey(1);
      usleep(10000);

  }
  delete image_server;
  return 0;
}

void window_callback(int event, int x, int y, int flags, void* userdata)
{
    // x = x - IMAGE_WIDTH/2;
    // y = y - IMAGE_HEIGHT;
     if  ( event == EVENT_LBUTTONDOWN )
     {
      /*
      baseLink= [240, 320]
      endpoint= [341.712, 426.705]
      */
      clicked_point = Point2d(x,y);
      clicked = true;
          // cout<<left_control.send_point(50,400,-400,375)<<'\n';
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
     }
}
