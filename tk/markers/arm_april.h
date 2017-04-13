#ifndef arm_april_h
#define arm_april_h value
#include <iostream>
#include <TagDetector.h>
#include <Geometry.h>
#include <DebugImage.h>
#include <opencv2/highgui/highgui.hpp>

#define DEFAULT_TAG_FAMILY "Tag16h5"


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
  Mat detection_image;
  Mat draw_image;

  cv::Point2d opticalCenter;

  TagFamily* tag_family;
  TagDetector* tag_detector;
  TagDetectionArray detections;

};


#endif
