#ifndef human_tracker_h
#define human_tracker_h 4
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <TLD.h>
// #include <TLDUtil.h>

using namespace cv;
using namespace std;
inline int detectMotion(Mat & motion, Mat & result, Mat & result_cropped,
                 Rect & search_box,Rect& bounding_box,Rect& occlusion_box,
                 int max_deviation,
                 Scalar & color);

class Human_Tracker
{

	public:
		Human_Tracker(Mat& input_frame);
		~Human_Tracker();
		int       	detect_arm(Mat& input_frame);
		bool      	detected();
		int			set_init_box(Rect input_box);
        int       	draw_box(Mat &draw_frame);
        int         get_box(Rect &out_box);
        int         set_robot(Rect & robot_box);
		Point2d   	get_position();
	private:
		Mat prev_frame;
		Mat curr_frame;
		Mat next_frame;
		Mat kernel_ero;
		Mat motion;
		Mat result, result_cropped;
	    int max_deviation,number_of_changes, number_of_sequence = 0;
	    Scalar mean_,box_color; // yellow

		int x_start, x_stop;
		int y_start, y_stop ;
        int x_start_max;
        int x_stop_max;
        int y_start_max;
        int y_stop_max;
		// Mat grey_space_frame;
		// TLD 			tld_tracker;
		// tld::Trajectory tld_trajectory;


		int		trajectoryLength = 0;
		float	confidence_threshold = .5;
		bool	arm_detected=false;
		bool	showNotConfident = true;
		int		skipProcessingOnce = 0;
		bool 	reuseFrameOnce = false;
		bool 	frame_received = false;
		Rect 	init_box;
		Rect 	bounding_box;
		Rect 	search_box;
        Rect    occlusion_box;

};

#endif
