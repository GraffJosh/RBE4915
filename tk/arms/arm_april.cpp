#include "arm_april.h"

TagTestOptions create_options(){
  TagTestOptions opts;
  opts.show_debug_info = false;
  opts.show_timing = true;
  opts.show_results = true;
  opts.be_verbose = true;
  opts.no_images = true;
  opts.generate_output_files = false;
  opts.params.segDecimate = false;//false is best
  // opts.params.sigma =;
  opts.params.segSigma =.8;
  opts.params.thetaThresh = 150;
  opts.params.magThresh =5000;
  // opts.params.adaptiveThresholdValue =1000;
  // opts.params.adaptiveThresholdRadius =10;
  opts.params.refineBad = true;
  opts.params.refineQuads = true;
  opts.params.newQuadAlgorithm = false;
  opts.family_str = DEFAULT_TAG_FAMILY;
  opts.error_fraction = 30;

  opts.params.adaptiveThresholdRadius += (opts.params.adaptiveThresholdRadius+1) % 2;
  return opts;
}

Arm_april::Arm_april(int fid_num,Mat& frame_ref, float forward,float back,float width)
{

  detection_image = frame_ref;
  arm_num= fid_num;

  front_len = forward;
  back_len = back;
  wid = width;


  //allocates space for the box.
  link2_box.resize(4);
  TagTestOptions opts = create_options();
  tag_family= new TagFamily(opts.family_str);
  tag_detector=new TagDetector(*tag_family, opts.params);
  opticalCenter = Point2d(0.5*detection_image.rows, 0.5*detection_image.cols);
  arm_tracker.set_rate(0);
}
Arm_april::~Arm_april()
{
  delete tag_family;
  delete tag_detector;
}


int Arm_april::detect_arm()
{
  tag_detector->process(detection_image, opticalCenter, detections);

  for (size_t i=0; i<detections.size(); ++i) {
    const TagDetection& d = detections[i];
    if(d.id == arm_num)
    {
      is_detected = true;
      arm_marker = d;
      arm_tracker.attach_marker(arm_marker);
      arm_tracker.filter();
    }
  }
  return detections.size();
}

int Arm_april::draw_markers(Mat& frame_ref)
{
  // cv::Mat img = tag_family.superimposeDetections(frame_ref, detections);
  // frame_ref = tag_family->superimposeDetections(frame_ref, detections);
  if(is_detected){
    frame_ref = tag_family->superimposeDetection(frame_ref, arm_marker);
    // std::cout << "arm: " << arm_marker.cxy <<'\n';
  }

}

bool Arm_april::detected()
{
  return is_detected;
}
int Arm_april::draw_box(Mat& frame_ref)
{
  if(is_detected)
  {
    link2_back = arm_tracker.interpolate(back_len,0);
    link2_front = arm_tracker.interpolate(front_len,0);
    link2_box.at(0) = arm_tracker.interpolate(front_len, wid);
    link2_box.at(1) = arm_tracker.interpolate(front_len, -wid);
    link2_box.at(2) = arm_tracker.interpolate(back_len, -wid);
    link2_box.at(3) = arm_tracker.interpolate(back_len, wid);
      for (int i = 0; i < 4; i++)
          line(frame_ref, link2_box.at(i), link2_box.at((i+1)%4), Scalar(0,255,0));
  }
}

void Arm_april::print_tags()
{
  for(auto & marker: detections)
  {
    std::cout << "marker: " <<marker.id<<" pos: "<<marker.cxy<< '\n';
  }
}

Point2d Arm_april::get_position()
{
  return arm_tracker.interpolate(front_len,0);
}
