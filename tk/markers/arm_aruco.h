#ifndef arm_aruco_h
#define arm_aruco_h value
#include <iostream>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <opencv2/highgui/highgui.hpp>
#include "../math.cpp"

using namespace std;
using namespace cv;
using namespace aruco;

class Arm_aruco{


public:
            Arm_aruco(int fid_num, Mat& frame_ptr);
            ~Arm_aruco();

  Marker    get_arm_marker();

  int       detect_arm();
  int       draw_markers(Mat& frame_ref);
  int       draw_box(Mat& frame_ref);

private:
  int arm_num;
  float rotation_angle;

  float link1_len;
  float link2_len;
  float link1_wid;
  float link2_wid;
  float marker_size;

  Mat rotation_matrix;
  Mat translation_matrix;

  Mat input_image;
  MarkerDetector aruco_detector;
  MarkerPoseTracker aruco_tracker;
  vector<Marker> Markers;
  Marker arm_marker;
  CameraParameters TheCameraParameters;


};


#endif
