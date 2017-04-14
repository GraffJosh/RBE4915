#include "arm_april.h"

TagTestOptions create_options(){
  TagTestOptions opts;
  opts.show_debug_info = false;
  opts.show_timing = true;
  opts.show_results = true;
  opts.be_verbose = true;
  opts.no_images = true;
  opts.generate_output_files = false;
  opts.params.segDecimate = false;
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
Arm_april::Arm_april(int fid_num, Mat& frame_ref)
{
  detection_image = frame_ref;
  draw_image = frame_ref;
  arm_num= fid_num;

  link2_for = -12;
  link2_aft = 6;
  link2_wid = 3.5;
  link1_len = 20;
  link1_wid = 3.5;
  marker_size = 46.0375f;//mm;//1.8125;//inches

  TagTestOptions opts = create_options();
  tag_family= new TagFamily(opts.family_str);
  tag_detector=new TagDetector(*tag_family, opts.params);
  opticalCenter = Point2d(0.5*detection_image.rows, 0.5*detection_image.cols);
  arm_tracker.set_rate(1);
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
      detected = true;
      arm_marker = d;
      arm_tracker.attach_marker(arm_marker);
      arm_tracker.filter();
      link2_front = arm_tracker.interpolate(link2_for, 0);
      link2_back = arm_tracker.interpolate(link2_aft,0);

    }
  }
}

int Arm_april::draw_markers(Mat& frame_ref)
{
  // cv::Mat img = tag_family.superimposeDetections(frame_ref, detections);
  // frame_ref = tag_family->superimposeDetections(frame_ref, detections);
  if(detected){
    frame_ref = tag_family->superimposeDetection(frame_ref, arm_marker);
    std::cout << "arm: " << arm_marker.cxy <<'\n';
  }

}
int Arm_april::draw_box(Mat& frame_ref)
{
  if(detected)
  {
      rectangle(frame_ref,  link2_back,
                        link2_front,
                        Scalar( 0, 255, 255 ),
                        0,8);
      rectangle(frame_ref,  arm_marker.interpolate(link2_for, 0),
                        arm_marker.interpolate(link2_aft,0),
                        Scalar( 255, 0, 255 ),
                        0,8);
}

}
