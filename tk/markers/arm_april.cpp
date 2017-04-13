#include "arm_april.h"

TagTestOptions create_options(){
  TagTestOptions opts;
  opts.show_debug_info = false;
  opts.show_timing = true;
  opts.show_results = true;
  opts.be_verbose = true;
  opts.no_images = true;
  opts.generate_output_files = true;
  opts.params.segDecimate = true;
  // opts.params.sigma =;
  // opts.params.segSigma =;
  // opts.params.thetaThresh =;
  // opts.params.magThresh =;
  // opts.params.adaptiveThresholdValue =;
  // opts.params.adaptiveThresholdRadius =;
  opts.params.refineBad = true;
  opts.params.refineQuads = true;
  opts.params.newQuadAlgorithm = true;
  opts.family_str = DEFAULT_TAG_FAMILY;
  opts.error_fraction = 1;

  opts.params.adaptiveThresholdRadius += (opts.params.adaptiveThresholdRadius+1) % 2;
  return opts;
}
Arm_april::Arm_april(int fid_num, Mat& frame_ref)
{
  detection_image = frame_ref;
  draw_image = frame_ref;
  arm_num= fid_num;

  link1_len = .85;//meters
  link2_len = .6;//meters
  link1_wid = .85;//meters
  link2_wid = .6;//meters

  marker_size = 2.0f;//0.0508f;




  TagTestOptions opts = create_options();
   tag_family= new TagFamily(opts.family_str);
   tag_detector=new TagDetector(*tag_family, opts.params);
  opticalCenter = Point2d(0.5*detection_image.rows, 0.5*detection_image.cols);
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
    std::cout << " - Detection: id = " << d.id << ", "
              << "code = " << d.code << ", "
              << "rotation = " << d.rotation << "\n";
            }
}

int Arm_april::draw_markers(Mat& frame_ref)
{
  // cv::Mat img = tag_family.superimposeDetections(frame_ref, detections);
  frame_ref = tag_family->superimposeDetections(frame_ref, detections);
}
