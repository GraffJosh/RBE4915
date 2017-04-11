#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "server.cpp"

using namespace udp_client_server;
using namespace cv;
using namespace std;
int main(int argc, char const *argv[]) {


  udp_client_server::udp_server image_server("192.168.10.6",1234);
  int width = 640;
  int height = 480;
  int received_frames = 0;
  cv::Mat received_frame = Mat::zeros(height,width,CV_8UC3);
  size_t frame_size = received_frame.total()*received_frame.elemSize();

  char msg[46097];
  while (1) {
    /* code */

    if(!image_server.receive_image(received_frame, frame_size))//.image_server.recv(msg,46097)
    {
      cv::imshow("frame",received_frame);
      std::cout << "frames received: " << received_frames << '\n';
      received_frames++;
      cv::waitKey(1);
    }
    // if(image_server.recv(msg,1024)>0){
    //   std::cout << msg << '\n';
    // }

  }


  return 0;
}
