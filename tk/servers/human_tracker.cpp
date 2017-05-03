#include "human_tracker.h"
using namespace cv;
using namespace std;
Human_Tracker::Human_Tracker(Mat& input_frame){
	Mat prev_frame = result = input_frame;
    Mat curr_frame = input_frame;
    Mat next_frame = input_frame;
    cvtColor(curr_frame, curr_frame, CV_RGB2GRAY);
    cvtColor(prev_frame, prev_frame, CV_RGB2GRAY);
    cvtColor(next_frame, next_frame, CV_RGB2GRAY);

	x_start_max = 10;
	x_stop_max = 640;
	y_start_max = 200;
	y_stop_max = 480;
	x_start = x_start_max;
	x_stop = x_stop_max;
	y_start = y_start_max;
	y_stop = y_stop_max;

	search_box = Rect(Point(10,200),Point(640,480));
	box_color = Scalar(0,0,255);

    // Maximum deviation of the image, the higher the value, the more motion is allowed
	max_deviation = 80;

	// Erode kernel
	kernel_ero = getStructuringElement(MORPH_RECT, Size(2,2));


}
Human_Tracker::~Human_Tracker(){


}


int Human_Tracker::detect_arm(Mat & input_frame)
{

	if(frame_received)
	{
		Mat d1, d2;
		Mat result, result_cropped;
		Scalar color = Scalar(0,0,255);

        prev_frame = curr_frame;
        curr_frame = next_frame;
        next_frame = input_frame;
        result = next_frame;
        cvtColor(next_frame, next_frame, CV_RGB2GRAY);


		if(prev_frame.cols >100)
		{
			//watches ~long term motion and such
	        absdiff(prev_frame, next_frame, d1);
	        absdiff(next_frame, curr_frame, d2);
	        bitwise_and(d1, d2, motion);
	        threshold(motion, motion, 30, 255, CV_THRESH_BINARY);
	        erode(motion, motion, kernel_ero);
			// blur(motion, motion, Size(3,3));
			// Canny(motion,motion,80, 100*3, 3);
			if(motion.cols>100) imshow("test",motion);

	        number_of_changes = detectMotion(motion, result, result_cropped,
				search_box,bounding_box,occlusion_box,
				max_deviation , color);

			if(number_of_changes>10)
			{
				arm_detected = true;
//this sizes the box in which the next run will search.
//this way, I only check areas where I've seen motion for more motion.
//detectMotion has logic to ignore the search box if a large enough portion of the image
//has changed.
				search_box = bounding_box;
				search_box += Size(50,50);
				search_box -= Point(25,25);
				if(search_box.br().y < motion.rows+10) search_box += Point(0,(search_box.height/2)+10);

			}else if(mean(motion)[0] > 5 && mean(motion)[0]<100){
				search_box = init_box;

			}


		}
		return number_of_changes;
	}else
	{
		return -1;
	}


}


//determines if a pixel has motion at it.
//options here can manage the occlusion box and neighbors
bool check_pixel(Mat & motion, int j, int i, Rect &occlusion_box)
{
	if( motion.at<int>(j,i) == 255
		//&& motion.at<int>(j,i-1) == 255
		//&& motion.at<int>(j-1,i) == 255 && motion.at<int>(j,i+1) == 255
		&& !occlusion_box.br().y < j+50)
		return true;
	else
		return false;
}

// Check if there is motion in the result matrix
// count the number of changes and return.
//searches within a search box, ignoring points in an occlusion box, and outputing a bounding box.
//result, result_cropped are not used. Motion is the input thresholded image.
inline int detectMotion(Mat & motion, Mat & result, Mat & result_cropped,
                 Rect & search_box,Rect& bounding_box,Rect& occlusion_box,
                 int max_deviation,
                 Scalar & color)
{
    // calculate the standard deviation
    Scalar mean, stddev;
    meanStdDev(motion, mean, stddev);
    // if not to much changes then the motion is real (neglect agressive snow, temporary sunlight)
    if(stddev[0] < max_deviation)
    {
        int number_of_changes = 0;
        int min_x = motion.cols, max_x = 0;
        int min_y = motion.rows, max_y = 0;
        // loop over image and detect changes
		for(int j = search_box.tl().y; j < (search_box.br().y >= min_y-10 ?search_box.br().y: min_y-10); j+=2){ // height
            for(int i = search_box.tl().x; i < search_box.br().x; i+=2){ // width
                // check if at pixel (j,i) intensity is equal to 255
                // this means that the pixel is different in the sequence
                // of images (prev_frame, curr_frame, next_frame)
                if(check_pixel(motion,j,i,occlusion_box))
                {
                    number_of_changes++;
                    // if(min_x>i) min_x = i;

					//this code determines the max (or minimum) y value of any motion.
//for detecting person
                    if(min_y>j)
					{
						if(min_x>i) min_x = i;
						if(max_x<i) max_x = i;
						max_y = j;
						min_y = j-5;
					}
//for detecting the robot
                    // if(max_y<j)
					// {
					// 	if(min_x>i) min_x = i;
					// 	if(max_x<i) max_x = i;
					// 	max_y = j;
					// 	min_y = j-5;
					// }
                }
            }
        }
        if(number_of_changes){
            //check if not out of bounds
            if(min_x-10 > 0){ min_x -= 10;}else{min_x = 0;}
            if(min_y-10 > 0){ min_y -= 10;}else{min_y = 0;}
            if(max_x+10 < result.cols-1){ max_x += 10;}else{max_x = result.cols-1;}
            if(max_y+10 < result.rows-1){ max_y += 10;}else{max_y = result.rows-1;}
            // draw rectangle round the changed pixel

            Point x(min_x,min_y);
            Point y(max_x,max_y);
			bounding_box = Rect(x,y);
			// if(bounding_box)
            // Mat cropped = result(bounding_box);
            // cropped.copyTo(result_cropped);
            // rectangle(result,rect,color,1);
        }
        return number_of_changes;
    }
    return 0;
}

//sets the initial search box.
int Human_Tracker::set_init_box(Rect input_box)
{
		search_box= input_box;
		init_box = input_box;
		frame_received = true;

}

//draws the found box on the frame.
int Human_Tracker::draw_box(Mat &draw_frame)
{
	if(detected())
	{
		rectangle(draw_frame, bounding_box, Scalar(255,0,0),2,1);
		rectangle(draw_frame, search_box, Scalar(0,255,0),1,1);
		rectangle(draw_frame, occlusion_box, Scalar(0,255,255),1,1);
	}
}
//returns the box of the motion
int Human_Tracker::get_box(Rect &out_box)
{
    if(detected())
    {
        out_box = bounding_box;
    }
}
//set the occlusion box.
int Human_Tracker::set_robot(Rect & robot_box)
{
	occlusion_box = robot_box;
}

bool Human_Tracker::detected()
{
	return arm_detected;//(number_of_changes >= confidence_threshold) ? true : false;
}

Point2d Human_Tracker::get_position(){
	Point2d ret_point;
	ret_point = bounding_box.tl();
	return ret_point;
}
