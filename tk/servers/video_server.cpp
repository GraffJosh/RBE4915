
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

  Arm_april human(6,proc_frame,2,-1,1);

  Aruco_Camera input_cam;
  input_cam.readFromXMLFile("Camera_Calib.yml");
  input_cam.resize(received_frame.size());
  // input_cam.calibrate();


  namedWindow("draw_window", 1);
  setMouseCallback("draw_window", window_callback, NULL);

  cout<<left_control.send_point(100,700,-300,200)<<'\n';

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
        proc_frame.copyTo(draw_frame);
        left_arm.detect_arm();
        human.detect_arm();
        left_arm.draw_box(draw_frame);
        human.draw_box(draw_frame);
        cv::imshow("draw_window",draw_frame);
    }

    if(human.detected() && left_control.is_ready())
    {
      left_control.send_point(100,input_cam.transformto_real(human.get_position()));
    }

    if(clicked)
    {
      Point3d transformed = input_cam.transformto_real(clicked_point);
      clicked = false;
      left_control.send_point(100,transformed);
    }
    cv::waitKey(1);
    usleep(100);

  }
  delete image_server;
  return 0;
}

void window_callback(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
      clicked_point = Point2d(x,y);
      clicked = true;
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
