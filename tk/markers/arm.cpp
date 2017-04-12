#include "arm.h"


Arm::Arm(int fid_num, Mat& frame_ref)
{
  arm_num = fid_num;
  input_image = frame_ref;

  link1_len = .85;//meters
  link2_len = .6;//meters
  link1_wid = .85;//meters
  link2_wid = .6;//meters

  marker_size = 0.0508f;

  TheCameraParameters.readFromXMLFile("Camera_Calib.yml");

}
Arm::~Arm()
{}

int Arm::detect_arm()
{
  aruco_detector.detect(input_image,Markers,TheCameraParameters,marker_size,false);
  // aruco_detector.detect(input_image,Markers,Mat(), Mat(),0.0508f,false);
  // calculateExtrinsics();
  return Markers.size();
}

int Arm::draw_markers(Mat& frame_ref)
{
  for (int i = 0; i < Markers.size(); i++) {
      auto marker = Markers.at(i);
      marker.draw(frame_ref,Scalar(0,0,255),1);
      CvDrawingUtils::draw3dCube(frame_ref, marker, TheCameraParameters);
      if(marker.id == arm_num)
      {
        arm_marker = marker;
      }
  }
}


int Arm::draw_box(Mat& frame_ref)
{
  std::vector<Point> corners;
  if(arm_marker.isValid() && aruco_tracker.estimatePose(arm_marker,TheCameraParameters,marker_size,1)){
      std::cout << "arm: " << arm_marker <<'\n';
      std::cout << aruco_tracker.getRTMatrix()<< '\n';

    // corners.push_back(Point())
  }
  return 0;
}
