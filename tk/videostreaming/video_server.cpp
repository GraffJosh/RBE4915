#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <future>
#include <iostream>
#include <pthread.h>
#include <arm_aruco.h>
// #include <arm_april.h>
#include "server.h"

using namespace udp_client_server;
using namespace cv;
using namespace std;
pthread_t receive_thread;
cv::Mat received_frame;
udp_client_server::udp_server* image_server;
void* get_images(void*)
{

  image_server->receive_image(received_frame.rows, received_frame.cols);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {



  int width = 640;
  int height = 480;
  int received_frames = 0;
  int num_markers = 0;

  VideoWriter outputVideo;
  if(argc>1)
  {
    string argument;
    argument.append(argv[argc-1]);
    outputVideo.open("output"+argument, 0, 10, Size(width,height), true);
  }

  received_frame = Mat::zeros(height,width,CV_8UC3);
  image_server = new udp_client_server::udp_server("192.168.10.5",1234);
  pthread_create(&receive_thread, NULL, get_images,NULL);

  Arm_aruco left_arm(1,received_frame);
  Mat proc_frame = Mat::zeros(height,width,CV_8UC3);
  Mat draw_frame = Mat::zeros(height,width,CV_8UC3);


  while (1) {

      switch (image_server->read_image(&received_frame))
      {
        case 0:
          // cv::imshow("frame",received_frame);
          if (outputVideo.isOpened())
          {
            outputVideo <<received_frame;
          }
          received_frames++;
          break;
        case 1:
          // cv::imshow("frame",received_frame);
          break;
        case -2:
          std::cout << "Mutex Error" << '\n';
          // usleep(100);
          continue;
      }


    if(received_frames >0 )
    {
          num_markers = left_arm.detect_arm();
          received_frame.copyTo(proc_frame);
          proc_frame.copyTo(draw_frame);
          left_arm.draw_markers(draw_frame);
          left_arm.draw_box(draw_frame);
          cv::imshow("frame",draw_frame);
    }
      // std::cout << "frames received: " << received_frames << '\n';
      cv::waitKey(1);
      usleep(10000);

  }
  delete image_server;
  return 0;
}
