#ifndef human_tracker_h
#define human_tracker_h 4
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <TLD.h>
// #include <TLDUtil.h>

using namespace cv;
using namespace std;
inline int detectMotion(const Mat & motion, Mat & result, Mat & result_cropped,
                 int& x_start, int& x_stop, int& y_start, int& y_stop,
                 int max_deviation,Rect& bounding_box,
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
		Rect 	bounding_box;

};

#endif
