#include <opencv\cv.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/tracking.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	namedWindow("Window 1", WINDOW_AUTOSIZE);
//	// List of tracker types in OpenCV 3.2
//	// NOTE : GOTURN implementation is buggy and does not work.
//	string trackerTypes[6] = { "BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN" };
//	// vector <string> trackerTypes(types, std::end(types));
//
//	// Create a tracker
//	string trackerType = trackerTypes[0];
//
//	Ptr<Tracker> tracker;
//
//#if (CV_MINOR_VERSION < 3)
//	{
//		tracker = Tracker::create(trackerType);
//	}
//#else
//	{
//		if (trackerType == "BOOSTING")
//			tracker = TrackerBoosting::create();
//		if (trackerType == "MIL")
//			tracker = TrackerMIL::create();
//		if (trackerType == "KCF")
//			tracker = TrackerKCF::create();
//		if (trackerType == "TLD")
//			tracker = TrackerTLD::create();
//		if (trackerType == "MEDIANFLOW")
//			tracker = TrackerMedianFlow::create();
//		if (trackerType == "GOTURN")
//			tracker = TrackerGOTURN::create();
//	}
//#endif
	Mat frame;

	// Read video
	VideoCapture video;

	video.open(0);
	//video.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	//video.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;

	}

	// Read first frame
	//bool ok = video.read(frame);

	// Define initial boundibg box
	//Rect2d bbox(287, 23, 86, 320);

	// Uncomment the line below to select a different bounding box
	//bbox = selectROI(frame, false);

	// Display bounding box.
	//rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
	//imshow("Tracking", frame);

	//tracker->init(frame, bbox);

	while (video.read(frame))
	{

		// Start timer
		//double timer = (double)getTickCount();

		//// Update the tracking result
		//bool ok = tracker->update(frame, bbox);

		//// Calculate Frames per second (FPS)
		//float fps = getTickFrequency() / ((double)getTickCount() - timer);


		//if (ok)
		//{
		//	// Tracking success : Draw the tracked object
		//	rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
		//}
		//else
		//{
		//	// Tracking failure detected.
		//	putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
		//}

		// Display tracker type on frame
		//putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		// Display FPS on frame
		//putText(frame, "FPS : " + SSTR(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		// Display frame.
		imshow("Window 1", frame);

		// Exit if ESC pressed.
		/*int k = waitKey(1);
		if (k == 27)
		{
			break;
		}
*/
	}



}