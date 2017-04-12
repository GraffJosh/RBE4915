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
  if(arm_marker.isValid() && aruco_tracker.estimatePose(arm_marker,TheCameraParameters,marker_size,4)){
    rotation_matrix = aruco_tracker.getRvec();
    translation_matrix = aruco_tracker.getTvec();
    rotation_angle = jpg_math::r_matrix_to_z_angle(rotation_matrix);
    std::cout << "rotation: " <<rotation_angle<< '\n';
  }
  // aruco_detector.detect(input_image,Markers,Mat(), Mat(),0.0508f,false);
  return Markers.size();
}

int Arm::draw_markers(Mat& frame_ref)
{
  for (int i = 0; i < Markers.size(); i++) {
      auto marker = Markers.at(i);
      marker.draw(frame_ref,Scalar(0,0,255),1);
      marker.calculateExtrinsics(marker_size,TheCameraParameters,false);
      rotation_angle = jpg_math::r_matrix_to_z_angle(marker.Rvec);
      std::cout << "rotation: " <<rotation_angle<< '\n';
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
  corners.push_back(Point(link2_len/2.0f, link2_wid/2.0f));
  corners.push_back(Point(link2_len/2.0f, -link2_wid/2.0f));
  corners.push_back(Point(-link2_len/2.0f, link2_wid/2.0f));
  corners.push_back(Point(-link2_len/2.0f, -link2_wid/2.0f));

  RotatedRect rRect = RotatedRect(Point2f(100,100), Size2f(link2_len,link2_wid), 30);
  Point2f vertices[4];
  rRect.points(vertices);
  for (int i = 0; i < 4; i++)
      line(frame_ref, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));

  if(arm_marker.isValid() && aruco_tracker.estimatePose(arm_marker,TheCameraParameters,marker_size,4)){
      std::cout << "arm: " << arm_marker <<'\n';
      // std::cout << aruco_tracker.getRTMatrix()<< '\n';
    // corners.push_back(Point())
  }
  return 0;
}
