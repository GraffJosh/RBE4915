/*
This file manages the tracking of the robot, including filtering of the robot's pose.

I believe that Arm_April constructs this object to filter/track the marker.
    in the future, it might be applied also to do more interested tracking mechanisms on
    humans and such.
*/
#include "tracker.h"

Tracker::Tracker(TagDetection* in_marker, float in_filter_rate)
{
  marker = in_marker;
  filter_rate= in_filter_rate;
  attached = true;
}
Tracker::Tracker(){}
Tracker::~Tracker(){}

//attach a marker to a constructed tracker.
//returns the ratio associated
int Tracker::attach_marker(TagDetection& in_marker)
{
  if(!isAttached() && in_marker.good)
  {
    marker = &in_marker;
    attached = true;
  }
}

bool Tracker::isAttached()
{
  return attached;
}

TagDetection* Tracker::get_marker()
{
  return marker;
}

//set the filtration ratio of the marker
int Tracker::set_rate(float in_filter_rate)
{
  filter_rate= in_filter_rate;
}

at::Mat Tracker::get_homography()
{
    return homographies.back();
}

at::Mat Tracker::filter()
{
  at::Mat filtered_homography;
  at::Mat ret_homography;
  if(marker->good)
  {
    //copy the homog over and add it to the list
    marker->homography.copyTo(filtered_homography);
    filtered_homography.copyTo(ret_homography);

    //add all the homographies together
    for(auto & homography : homographies)
    {
      add(homography,ret_homography,ret_homography);
    }


    //divide by num+1 (because we added the first homog to itself)
    ret_homography /= homographies.size()+1;

    if(homographies.size()>filter_rate)
    {
      homographies.erase(homographies.begin());
    }
  }
  homographies.push_back(ret_homography);
  // printf("Tracking 1 marker in %d history\n",(int)homographies.size() );
  return ret_homography;
}


at::Point Tracker::interpolate(at::real x, at::real y) const {
  const at::Mat& H = homographies.back();
  at::real z = H[2][0]*x + H[2][1]*y + H[2][2];
  return at::Point( (H[0][0]*x + H[0][1]*y + H[0][2])/z + marker->hxy.x,
                    (H[1][0]*x + H[1][1]*y + H[1][2])/z + marker->hxy.y );
}

at::Point Tracker::interpolate(const at::Point& p) const {
  return interpolate(p.x, p.y);
}
