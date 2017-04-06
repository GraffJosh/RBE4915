#include "highgui.h"
#include "cv.h"
#define CV_H
#include <iostream>
#include <conio.h>
#include "UDPClient.h"
using namespace std;
using namespace cv;

char *addr = "127.0.0.1";
int port = 9999;

int main(){
	cout<<"=== VIDEO SENDER ==="<<endl;

	//setup UDP client:
	UDPClient *client = new UDPClient(addr, port);

	//setup openCV
	cvNamedWindow("UDP Video Sender", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateCameraCapture(0);
	if(!capture){
		cout<<"No camera found."<<endl;
		goto DONE;
	}
	IplImage *frame;
	frame = cvQueryFrame(capture);
	IplImage *small = cvCreateImage(cvSize(frame->width / 2, frame->height / 2),
		frame->depth, 3);

	while(1){
		//capture frame and resize
		frame = cvQueryFrame(capture);
		cvResize(frame, small, CV_INTER_LINEAR);
		cvShowImage("UDP Video Sender", small);


		//send
		int result = client->sendData((char*)(&buff[0]), buff.size());
		if(result < 0)
			cout<<"Failed to send."<<endl;
		else
			cout<<"Sent a frame of size "<<result<<endl;

		cvWaitKey(15);
	}

	goto DONE;

DONE:
	cout<<"Press any key to continue."<<endl;
	getch();
}

/*
int main()
{
   cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE );
   CvCapture* capture = cvCreateCameraCapture(0);

   IplImage* frame;
       frame = cvQueryFrame( capture );
    if(!frame) return 0;
    int width = frame->width;
    int height = frame->height;

   while(1){

    IplImage* imgOld = cvCreateImage(cvSize(width/2,height/2),frame->depth,3);
    cvResize(frame,imgOld,CV_INTER_LINEAR);
    //cvCopy(frame1,img);
  frame = cvQueryFrame( capture ); 
    IplImage* imgNew = cvCreateImage(cvSize(width/2,height/2),frame->depth,3);
    cvResize(frame,imgNew,CV_INTER_LINEAR);
  cvAbsDiff(imgOld,imgNew,imgOld);
  //cvAddS(frame1,cvScalar(150,150,150),frame1);

  IplImage *im_gray = cvCreateImage(cvGetSize(imgOld),IPL_DEPTH_8U,1);
  cvCvtColor(imgOld,im_gray,CV_RGB2GRAY);
  

  cvThreshold( im_gray, im_gray, 30, 30, CV_THRESH_TOZERO );
  cvThreshold( im_gray, im_gray, 30, 255, CV_THRESH_BINARY );

  cvCvtColor(im_gray,imgOld,CV_GRAY2RGB);

  cvNot(imgOld,imgOld);

  cvSub(imgNew,imgOld,imgOld);

  cout<<"Original size: "<<imgNew->imageSize<<endl;
        //Mat src = imread("photo.bmp");
  Mat src(imgOld);

        //jpeg compression
        vector<uchar> buff;//buffer for coding
        vector<int> param = vector<int>(2);
        param[0]=CV_IMWRITE_JPEG_QUALITY;
        param[1]=20;//default(95) 0-100
        imencode(".jpg",src,buff,param);
        cout<<"JPEG size: "<<buff.size()<<endl;

  Mat jpegimage = imdecode(Mat(buff),CV_LOAD_IMAGE_COLOR);
  IplImage dst_img = jpegimage;

     cvShowImage( "Example2", &dst_img );
  //frame1=frame2;

     char c = cvWaitKey(50);
     if( c == 27 ) break;
  frame = cvQueryFrame( capture );
   }
   cvReleaseCapture( &capture );
   cvDestroyWindow( "Example2" );
}
*/