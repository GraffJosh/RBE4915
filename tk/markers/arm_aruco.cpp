#include "arm_aruco.h"


Arm_aruco::Arm_aruco(int fid_num, Mat& frame_ref)
{
  arm_num = fid_num;
  input_image = frame_ref;

  link1_len = .85;//inches
  link2_len = .6;//inches
  link1_wid = .85;//inches
  link2_wid = .6;//inches

  marker_size = 2.0f;//0.0508f; //inches

  TheCameraParameters.readFromXMLFile("Camera_Calib.yml");
  TheCameraParameters.resize(input_image.size());
  aruco_detector.setThresholdParams(7, 7);
  aruco_detector.setThresholdParamRange(2, 0);
}
Arm_aruco::~Arm_aruco()
{}

int Arm_aruco::detect_arm()
{
  aruco_detector.detect(input_image,Markers,TheCameraParameters,marker_size,false);
  imshow("thresholded",aruco_detector.getThresholdedImage());


  if(arm_marker.isValid() && aruco_tracker.estimatePose(arm_marker,TheCameraParameters,marker_size))
  {
    rotation_matrix = aruco_tracker.getRvec();
    translation_matrix = aruco_tracker.getTvec();
    std::cout << "tracking"<<translation_matrix << '\n';
  }
  // if(arm_marker.isValid() && aruco_tracker.estimatePose(arm_marker,TheCameraParameters,marker_size,2)){
  //   rotation_angle = jpg_math::r_matrix_to_z_angle(rotation_matrix);
  //   std::cout << "rotation: " <<jpg_math::rad2deg(rotation_angle)<< '\n';
  // }
  // aruco_detector.detect(input_image,Markers,Mat(), Mat(),0.0508f,false);
  return Markers.size();
}

int Arm_aruco::draw_markers(Mat& frame_ref)
{
  for (auto & marker:Markers) {
      // auto marker = Markers.at(i);
      marker.draw(frame_ref,Scalar(0,0,255),1);
      // marker.calculateExtrinsics(marker_size,TheCameraParameters,false);
      // rotation_angle = jpg_math::r_matrix_to_z_angle(marker.Rvec);
      // std::cout << "rotation: " <<rotation_angle<< '\n';
      if(marker.id == arm_num)
      {
        arm_marker = marker;
      }
  }
  if(rotation_matrix.empty() || translation_matrix.empty()){}else{
    CvDrawingUtils::draw3dAxis(frame_ref, TheCameraParameters,rotation_matrix,translation_matrix,2);
  }
  // for(auto & marker:Markers)
  // {
  //
  //   // CvDrawingUtils::draw3dCube(frame_ref, marker, TheCameraParameters);
  //   CvDrawingUtils::draw3dAxis(frame_ref, marker,TheCameraParameters);
  //   rotation_angle = jpg_math::r_matrix_to_z_angle(arm_marker.Rvec);
  //   std::cout << "rotation: " <<rotation_angle<<" "<< arm_marker.Rvec<< '\n';
  // }
}


int Arm_aruco::draw_box(Mat& frame_ref)
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
      // std::cout << "arm: " << arm_marker <<'\n';
      // std::cout << aruco_tracker.getRTMatrix()<< '\n';
    // corners.push_back(Point())
  }
  return 0;
}
