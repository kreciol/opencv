/**
* @function cornerDetector_Demo.cpp
* @brief Demo code for detecting corners using OpenCV built-in functions
* @author OpenCV team
*/

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <sstream>
#include <string>
#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>

#include <math.h>       /* tan */

#include "MySender.h"

#define PI 3.14159265

using namespace std;
using namespace cv;
//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 20;
int H_MAX = 160;
int S_MIN = 100;
int S_MAX = 255;
int V_MIN = 120;
int V_MAX = 256;
int MAX = 256;

double lastx = -1;
double lasty = -1;

//default capture width and height
const int FRAME_WIDTH = 1280;
const int FRAME_HEIGHT = 720;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 9;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";
Rect2d bbox = Rect2d(0, 310, 1280, 20); // selectROI(cameraFeed, false);
Mat table = Mat(512, 512, CV_8U);

MySender sender;


// ------------------------- MQTT START ---------------------------------------
bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void sendLineTo(int x, int y) {
	std::string message("{\"type\":\"line\",\"data\" : {\"x\" : $xPos,\"y\" : $yPos}}");
	std::string xPos = std::to_string(x);
	replace(message, "$xPos", xPos);
	std::string yPos = std::to_string(y);
	replace(message, "$yPos", yPos);
	sender.sendMessage(message.c_str());
}

void sendMoveTo(int x, int y) {
	std::string message("{\"type\":\"move\",\"data\" : {\"x\" : $xPos,\"y\" : $yPos}}");
	std::string xPos = std::to_string(x);
	replace(message, "$xPos", xPos);
	std::string yPos = std::to_string(y);
	replace(message, "$yPos", yPos);
	sender.sendMessage(message.c_str());
}

void sendClear() {
	std::string message("{\"type\":\"clear\"}");
	sender.sendMessage(message.c_str());
}

// ------------------------- MQTT END ----------------------------------------

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed





}
string intToString(int number) {


	std::stringstream ss;
	ss << number;
	return ss.str();
}
void createTrackbars() {
	//create window for trackbars

	namedWindow("table");
	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, MAX, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, MAX, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, MAX, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, MAX, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, MAX, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, MAX, on_trackbar);


}
void drawObject(int x, int y, Mat &frame) {

	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!

	//UPDATE:JUNE 18TH, 2013
	//added 'if' and 'else' statements to prevent
	//memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

	circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
	/*if (y - 25 > 0)
		line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
	if (y + 25 < FRAME_HEIGHT)
		line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
	if (x - 25 > 0)
		line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
	if (x + 25 < FRAME_WIDTH)
		line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);*/

	putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);

}
void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	//Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	//erode(thresh, thresh, erodeElement);
	//erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);



}
void trackFilteredObject(int &x, Mat threshold, Mat &cameraFeed) {
	int y = -1;
	x = -1;
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects < MAX_NUM_OBJECTS) {
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if (area > MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {
					x = moment.m10 / area;
					y = moment.m01 / area;
					objectFound = true;
					refArea = area;
				}
				else {
					objectFound = false;
				}

			}
			////let user know you found an object
			//if (objectFound == true) {
			//	putText(cameraFeed, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
			//	//draw object location on screen
			//	drawObject(x, y, cameraFeed);
			//}

		}
		else
		{
			//putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
		}
	}
}


void thresholdImage(Mat &thresh, int maximum, int minimum) {
	Mat temp;

	threshold(thresh, temp, maximum, 0, THRESH_TOZERO_INV);
	threshold(temp, thresh, minimum, 255, THRESH_BINARY);
}

VideoCapture setupCamera(int camera) {
	VideoCapture capture;
	capture.open(camera);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	//capture.set(CV_CAP_PROP_BRIGHTNESS, 30.0);
	//capture.set(CV_CAP_PROP_CONTRAST, 5.0);
	//capture.set(CV_CAP_PROP_SATURATION, 200.0);
	//capture.set(CV_CAP_PROP_EXPOSURE, -6.0);
	//capture.set(CV_CAP_PROP_WHITE_BALANCE_RED_V, 2500);
	//capture.set(CV_CAP_PROP_WHITE_BALANCE_BLUE_U, 2500);
	return capture;
}

Mat getLaserFrame(Mat camera)
{
	//camera = Mat(camera, bbox).clone();

	Mat HSV;
	Mat threshold;

	//convert frame from BGR to HSV colorspace
	cvtColor(camera, HSV, COLOR_BGR2HSV);

	vector<Mat> channel(3);


	split(HSV, channel);

	//imshow(windowName1, HSV);

	thresholdImage(channel[0], H_MAX, H_MIN);
	bitwise_not(channel[0], channel[0]);
	thresholdImage(channel[1], S_MAX, S_MIN);
	thresholdImage(channel[2], V_MAX, V_MIN);

	morphOps(channel[0]);
	morphOps(channel[1]);
	morphOps(channel[2]);

	//imshow("H", channel[0]);
	//imshow("S", channel[1]);
	//imshow("V", channel[2]);

	merge(channel, threshold);

	//imshow(windowName2, threshold);


	Mat laser;

	bitwise_and(channel[0], channel[2], laser);

	bitwise_and(channel[1], laser, laser);

	return laser;
}

double toRadians(double value) {
	return value / 180 * PI;
}

double toDeg(double value) {
	return value / PI * 180;
}

double getCameraAngle(double value)
{
	double virtualCameraConeBottomAngle = (180.0 - 67.309) / 2.0;
	double virtualCameraConeBottomAngleRad = toRadians(virtualCameraConeBottomAngle);
	double virtualCameraConeBottomLength = 1.084;
	double detectedPointPositionOnVirtualCameraCone = value / 1280.0 * virtualCameraConeBottomLength;

	double topFormula = sin(virtualCameraConeBottomAngleRad) * detectedPointPositionOnVirtualCameraCone;
	double bottomFormula = sqrt(1 + pow(detectedPointPositionOnVirtualCameraCone, 2) - (2 * cos(virtualCameraConeBottomAngleRad) * detectedPointPositionOnVirtualCameraCone));

	return asin(topFormula / bottomFormula);
}

void drawPoint(int a1, int a2) {
	if (a1 < 0 || a2 < 0) {
		lastx = -1;
		lasty = -1;
		return;
	}

	int x1 = 0;
	int y1 = 512;
	int x2 = 512;
	int y2 = 512;

	double alfa1 = 180.0 - (67.309 - toDeg(getCameraAngle(a1)));
	double alfa2 = toDeg(getCameraAngle(a2));

	double tan1 = tan(toRadians(alfa1));
	double tan2 = tan(toRadians(alfa2));

	double b1 = y1 - tan1*x1;
	double b2 = y2 - tan2*x2;

	double x = (b2 - b1) / (tan1 - tan2);
	double y = tan1*x + b1;

	y = 512 - y;

	//table = Mat(512, 512, CV_8U);

	Point start = lastx == -1 ? Point(x, y) : Point(lastx, lasty);

	//TODO;tutaj
	sendLineTo(x, y);

	line(table, start, Point(x, y), Scalar(0, 255, 0));
	//circle(table, Point(x, y), 1, Scalar(0, 255, 0), 1);
	//putText(table,  "A1: " + to_string(int(alfa1)) + " A2: " + to_string(int(alfa2)), Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
	imshow("table", table);

	lastx = x;
	lasty = y;
}

int main(int argc, char* argv[])
{
	cout << "Starting sender...\n";

	sender.initialize();
	sender.connectToServer();

	//Matrix to store each frame of the webcam feed
	Mat cameraFeed1;
	Mat cameraFeed2;

	//x and y values for the location of the object
	int a1 = 0, a2 = 0;
	//create slider bars for HSV filtering
	createTrackbars();

	VideoCapture capture1 = setupCamera(0);
	//VideoCapture capture2 = setupCamera(2);


	while (1) {
		//store image to matrix
		capture1.read(cameraFeed1);
		cameraFeed2 = cameraFeed1.clone();
		//capture2.read(cameraFeed2);

		cameraFeed1 = Mat(cameraFeed1, bbox).clone();
		cameraFeed2 = Mat(cameraFeed2, bbox).clone();

		Mat laser1 = getLaserFrame(cameraFeed1);
		Mat laser2 = getLaserFrame(cameraFeed2);

		trackFilteredObject(a1, laser1, cameraFeed1);
		trackFilteredObject(a2, laser2, cameraFeed2);

		//show frames 
		imshow("Camera1", cameraFeed1);
		imshow("Camera2", cameraFeed2);
		imshow("Laser1", laser1);
		imshow("Laser2", laser2);

		drawPoint(a1, a2);

		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		waitKey(30);
	}

	return 0;
}
