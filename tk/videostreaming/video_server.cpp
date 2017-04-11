#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <future>
#include <iostream>
#include <pthread.h>
#include "server.cpp"

using namespace udp_client_server;
using namespace cv;
using namespace std;
pthread_t receive_thread;
cv::Mat received_frame;
udp_client_server::udp_server* image_server;
void* get_images(void*)
{

  image_server->receive_image(&received_frame,received_frame.rows, received_frame.cols);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  int width = 640;
  int height = 480;
  int received_frames = 0;
  received_frame = Mat::zeros(height,width,CV_8UC3);

  image_server = new udp_client_server::udp_server("192.168.10.5",1234);

  pthread_create(&receive_thread, NULL, get_images,NULL);

  while (1) {
    /* code */
    if(image_server->image_received)
    {
      if(image_server->copy_mutex.try_lock())
      {
        cv::imshow("frame",received_frame);
        image_server->copy_mutex.unlock();
      }else{
        continue;
      }
      std::cout << "frames received: " << received_frames << '\n';
      received_frames++;
      cv::waitKey(1);
    }


        usleep(10000);
    // if(!image_server.receive_image(received_frame, frame_size))
    // {
    //   cv::imshow("frame",received_frame);
    //   std::cout << "frames received: " << received_frames << '\n';
    //   received_frames++;
    //   cv::waitKey(1);
    // }

  }
  delete image_server;
  return 0;
}
