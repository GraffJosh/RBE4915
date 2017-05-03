/*
Basic math stuff for use in other programs.
*/

#ifndef jpg_math_h
#define jpg_math_h val
#include <opencv2/core/core.hpp>
using namespace cv;
namespace jpg_math
{
    // Checks if a matrix is a valid rotation matrix.
  static bool isRotationMatrix(Mat &R)
  {
      Mat Rt;
      transpose(R, Rt);
      Mat shouldBeIdentity = Rt * R;
      Mat I = Mat::eye(3,3, shouldBeIdentity.type());

      return  norm(I, shouldBeIdentity) < 1e-6;

  }

  // Calculates rotation matrix to euler angles
  // The result is the same as MATLAB except the order
  // of the euler angles ( x and z are swapped ).
  static Vec3f rotationMatrixToEulerAngles(Mat &R)
  {

      assert(isRotationMatrix(R));

      float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

      bool singular = sy < 1e-6; // If

      float x, y, z;
      if (!singular)
      {
          x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
          y = atan2(-R.at<double>(2,0), sy);
          z = atan2(R.at<double>(1,0), R.at<double>(0,0));
      }
      else
      {
          x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
          y = atan2(-R.at<double>(2,0), sy);
          z = 0;
      }
      return Vec3f(x, y, z);



  }

  static float r_matrix_to_z_angle(Mat &R)
  {
    float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

    bool singular = sy < 1e-6; // If
    if(!singular)
      return atan2(R.at<double>(1,0), R.at<double>(0,0));
    else
      return -1;
  }
  static float r_matrix_to_y_angle(Mat &R)
  {
    float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

    bool singular = sy < 1e-6; // If
    if(!singular)
      return atan2(-R.at<double>(2,0), sy);
    else
      return -1;
  }




  inline double deg2rad (double degrees) {
    static const double pi_on_180 = 4.0 * atan (1.0) / 180.0;
    return degrees * pi_on_180;
  }
  inline double rad2deg (double degrees) {
    static const double pi_on_180 = 180.0 / 4.0 * atan (1.0);
    return degrees * pi_on_180;
  }

}
#endif
