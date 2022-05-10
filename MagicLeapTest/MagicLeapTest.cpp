#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


 int main() {

	string path = "MagicLeapFront.png";
	Mat img, mLeap, mLeapHSV, mask, transparent;
	VideoCapture capture(0);

	if (!capture.isOpened()) {
		cerr << "Error opening the webcam!" << endl;
		return -1;
	}

	mLeap = imread(path);

	int hmin = 0, hmax = 173, smin = 24, smax = 255, vmin = 0, vmax = 255;

	/*namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);*/

	//get mask for magic leap frame
	Scalar min(hmin, smin, vmin);
	Scalar max(hmax, smax, vmax);

	cvtColor(mLeap, mLeapHSV, COLOR_BGR2HSV);
	inRange(mLeapHSV, min, max, mask);



	//view magic leap with transparent background
	imshow("Magic Leap", mask);
	waitKey(1);
	

	/*while (true) {

		capture.read(img);
		imshow("image", img);
		waitKey(1);
	}*/

	return 0;
}