#ifndef arm_april_h
#define arm_april_h 3
#include <iostream>
#include "apriltags-cpp/src/TagDetector.h"
#include "apriltags-cpp/src/Geometry.h"
#include "apriltags-cpp/src/DebugImage.h"
#include <opencv2/highgui/highgui.hpp>
#include "tracker.h"

#define DEFAULT_TAG_FAMILY "Tag16h5"
#define link2_for -8
#define link2_aft 3
#define link2_wid 1.5
#define link1_len 20
#define link1_wid 3.5
#define marker_size 46.0375f//mm;//1.8125;//inche


using namespace std;
using namespace cv;

typedef struct TagTestOptions {
  TagTestOptions() :
      show_debug_info(false),
      show_timing(false),
      show_results(false),
      be_verbose(false),
      no_images(false),
      generate_output_files(false),
      params(),
      family_str(DEFAULT_TAG_FAMILY),
      error_fraction(1){
  }
  bool show_debug_info;
  bool show_timing;
  bool show_results;
  bool be_verbose;
  bool no_images;
  bool generate_output_files;
  TagDetectorParams params;
  std::string family_str;
  double error_fraction;
} TagTestOptions;


class Arm_april{


public:
            Arm_april(int fid_num, Mat& frame_ptr);
            ~Arm_april();


  int       detect_arm();
  int       draw_markers(Mat& frame_ref);
  int       draw_box(Mat& frame_ref);
  void      print_tags();
  Point2d   get_position();

private:
  int arm_num;
  float rotation_angle;
  bool detected=false;

  std::vector<Point2d> link2_box;
  Point2d link1_front;
  Point2d link2_front;
  Point2d link1_back;
  Point2d link2_back;

  Mat rotation_matrix;
  Mat translation_matrix;
  Mat detection_image;
  Mat draw_image;

  cv::Point2d opticalCenter;
  TagFamily* tag_family;
  TagDetector* tag_detector;
  TagDetection arm_marker;
  TagDetectionArray detections;
  Tracker arm_tracker;


};


#endif
