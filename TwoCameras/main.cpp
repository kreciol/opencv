#include <opencv\cv.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;

//default capture width and height
const int FRAME_WIDTH = 1280;
const int FRAME_HEIGHT = 720;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20 * 20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;

int main(int argc, char* argv[])
{
	namedWindow("Camera 1", WINDOW_AUTOSIZE);
	namedWindow("Camera 2", WINDOW_AUTOSIZE);

	// Ptr<Tracker> tracker = TrackerBoosting::create();
	// Ptr<Tracker> tracker = TrackerMIL::create();
	// Ptr<Tracker> tracker = TrackerKCF::create();
	// Ptr<Tracker> tracker = TrackerTLD::create();
	// Ptr<Tracker> tracker = TrackerMedianFlow::create();
	// Ptr<Tracker> tracker = TrackerGOTURN::create();

	Mat cameraFeed1;
	
	VideoCapture capture1;
	capture1.open(0);
	capture1.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture1.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	Mat cameraFeed2;

	VideoCapture capture2;
	capture2.open(1);
	capture2.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture2.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);


	/*for (int i = 0; i < 100; i++)
	{
		capture1.read(cameraFeed1);
		imshow("Camera 1", cameraFeed1);
	}*/

	//Rect2d bbox = selectROI(cameraFeed1, false);
	//rectangle(cameraFeed1, bbox, Scalar(255, 0, 0), 2, 1);

	//tracker->init(cameraFeed1, bbox);

	// int x = 0, y = 0;

	while (1) {
		capture1.read(cameraFeed1);
		imshow("Camera 1", cameraFeed1);

		capture2.read(cameraFeed2);
		imshow("Camera 2", cameraFeed2);



		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		waitKey(30);
	}


	return 0;
}

