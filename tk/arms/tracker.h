#ifndef tracker_h
#define tracker_h 3

#include <iostream>
#include <opencv2/core/core.hpp>
#include "apriltags-cpp/src/TagDetector.h"
#include "apriltags-cpp/src/Geometry.h"
#include "apriltags-cpp/src/DebugImage.h"
#include "apriltags-cpp/src/AprilTypes.h"

using namespace cv;
using namespace std;

class Tracker{
public:
  Tracker(TagDetection* in_marker, float in_filter_rate);
  Tracker();
  ~Tracker();

  int attach_marker(TagDetection& in_marker);
  int set_rate(float in_filter_rate);
  TagDetection* get_marker();
  bool isAttached();
  at::Mat filter();
  at::Point interpolate(at::real x, at::real y) const;
  at::Point interpolate(const at::Point& p) const;
  at::Mat get_homography();
private:
  float filter_rate;
  bool attached=false;
  vector<at::Mat> homographies;
  TagDetection* marker;



};



#endif
