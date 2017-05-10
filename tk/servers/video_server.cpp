/*
This file manages the main loop for the vision system. It initializes the objects to
    control the robot, track the robot, and track motion inside the camera frame.

It also manages retreiving images from the video server object in a separate thread.

The file is also an excellent control mechanism, as it can transform from the camera
    frame to the robot frame and send commands to that robot.  
*/



#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <future>
#include <iostream>
#include <pthread.h>
//#include <arm_aruco.h>
#include <arm_april.h>
#include <arm_control.h>
#include "human_tracker.h"
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
    Arm_april left_arm(11,proc_frame);                                //tracking and arm management
    Arm_april num_6_tag(6,proc_frame,2,-1,1);

    Arm_Control left_control(1,"192.168.10.64",5005);

    Human_Tracker human(proc_frame);//, arm_box);

    Rect left_robot;
    Aruco_Camera input_cam;
    input_cam.readFromXMLFile("Camera_Calib.yml");
    input_cam.resize(received_frame.size());


    namedWindow("draw_window", 1);
    setMouseCallback("draw_window", window_callback, NULL);
if(left_control.is_connected())

  while (1) {

      //manages the collection of frames from the image server the switch case is
      //for tracking the mutex of the frame retrieval.
      switch (image_server->read_image(&received_frame))
      {
        case 0:
            //new frame.
          if (outputVideo.isOpened())
          { outputVideo <<received_frame;}
          undistort(received_frame,proc_frame, input_cam.CameraMatrix,input_cam.Distorsion);
          received_frames++;
          break;
        case 1:
            //no new frame.
          break;
        case -2:
            //mutex failure
          usleep(100);
          continue;
      }


      //do detection and processing.
    if(received_frames >0 )
    {
        proc_frame.copyTo(draw_frame);
        left_arm.detect_arm();
        left_arm.draw_box(draw_frame);
        num_6_tag.detect_arm();
        left_robot = left_arm.get_box();
        human.set_robot(left_robot);
        human.detect_arm(proc_frame);
        human.draw_box(draw_frame);
        cv::imshow("draw_window",draw_frame);
    }
    if(left_arm.detected() && !human.detected())// && left_control.is_ready())
    {
        human.set_init_box(Rect(Point(10,200),Point(640,480)));
      //left_control.send_point(100,input_cam.transformto_real(human.get_position()));
    }

    //follow the person's hand.
    if(human.detected() && left_control.is_ready())
    {
        int send_x = 200;
        int send_y = human.get_position().y;
        Point3d transformed = input_cam.transformto_real(Point(send_x,send_y));
    }else{
    }
    //if we're connected to the robot, and somebody has clicked,
    //send the robot to that point.
    if(left_control.is_connected() && clicked)
    {
      Point3d transformed = input_cam.transformto_real(clicked_point);
      clicked = false;
      left_control.send_point(100,transformed);
      std::cout << "clicked: " <<clicked_point<< '\n';
    }
    cv::waitKey(1);
    usleep(10);

  }
  delete image_server;
  return 0;
}


//manages cursor input to the image window.
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
