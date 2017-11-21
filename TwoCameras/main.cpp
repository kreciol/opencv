#include <opencv\cv.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	namedWindow("Camera 1", WINDOW_AUTOSIZE);
	//namedWindow("Camera 2", WINDOW_AUTOSIZE);

	Ptr<Tracker> tracker = TrackerMedianFlow::create();

	Mat cameraFeed1;
	
	VideoCapture capture1;
	capture1.open(0);
	capture1.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	capture1.set(CV_CAP_PROP_FRAME_HEIGHT, 600);

	//Mat cameraFeed2;

	//VideoCapture capture2;
	//capture2.open(1);
	//capture2.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	//capture2.set(CV_CAP_PROP_FRAME_HEIGHT, 600);

	capture1.read(cameraFeed1);

	Rect2d bbox = selectROI(cameraFeed1, false);
	rectangle(cameraFeed1, bbox, Scalar(255, 0, 0), 2, 1);
	imshow("Camera 1", cameraFeed1);

	tracker->init(cameraFeed1, bbox);

	while (1) {
		capture1.read(cameraFeed1);

		//capture2.read(cameraFeed2);
		//imshow("Camera 2", cameraFeed2);

		// Update the tracking result
		bool ok = tracker->update(cameraFeed1, bbox);

		if (ok)
		{
			// Tracking success : Draw the tracked object
			rectangle(cameraFeed1, bbox, Scalar(255, 0, 0), 2, 1);
		}
		else
		{
			// Tracking failure detected.
			putText(cameraFeed1, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
		}

		imshow("Camera 1", cameraFeed1);


		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		waitKey(30);
	}


	return 0;
}