#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/video.hpp>
using namespace cv;
void video();
int main(int argc, char const *argv[]) {
  cv::Mat ray = cv::imread("ray.jpg");
  cv::Mat dst;

  video();


  return 0;
}



void process(){
  Mat img_processed, img;
  resize(img,img_processed,Size(img.cols/2,img.rows/2));

  Mat R = getRotationMatrix2D(Point2f(img.cols/2,img.rows/2),45,1);

  warpAffine(img, img_processed,R,img.size());

  Canny(img,img_processed,200,300);

  for (size_t i = 1; i < 20; i+=2) {
    Mat img_blurred;
    cv::blur(img,img_blurred,Size(i,i));
    cv::Canny(img_blurred,img_processed,100,150);


      cv::imshow("img",img);
      cv::imshow("img_blurred",img_blurred);
      cv::imshow("resize",img_processed);
      cv::waitKey();
  }
}


void video(){

  cv::Mat img,img_prev;
  cv::VideoCapture input(0);
  cv::OrbFeatureDetector detector;
  std::vector<KeyPoint> keypoints;
  std::vector<Point2f> points,points_prev;
  std::vector<uchar> status;
  std::vector<float> error;


  input.read(img);
  detector(img,Mat(),keypoints);
  KeyPoint::convert(keypoints,points);
  img.copyTo(img_prev);
  points_prev = points;

  for (;;)
  {
    if (!input.read(img))
    {  break;
    }

      calcOpticalFlowPyrLK(
        img_prev, img, points_prev,points,status,error);
        img.copyTo(img_prev);

    for (int i = 0; i < points.size(); i++) {
      circle(img,points[i] ,2,Scalar(0,2,norm(points_prev[i]-points[i])*20),3);
    }
    points_prev = points;
    cv::imshow("img",img);

    char c = cv::waitKey(30);

    if(c==' ')
      break;
  }
}
