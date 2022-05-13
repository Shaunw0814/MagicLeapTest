#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


 int main(int argc, char** argv) {

	Mat img, mLeap, blur, mLeapHSV, alpha;
	VideoCapture capture(0);

	if (!capture.isOpened()) {
		cerr << "Error opening the webcam!" << endl;
		return -1;
	}

	mLeap = imread("MagicLeapFront.png");
	alpha = imread("alpha.png");

	//face detection
	CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml");

	//removing background
	mLeap.convertTo(mLeap, CV_32FC3);
	alpha.convertTo(alpha, CV_32FC3, 1.0 / 255);
	Mat result = Mat::zeros(mLeap.size(), mLeap.type());

	multiply(alpha, mLeap, mLeap);

	alpha.convertTo(alpha, CV_8U);
	mLeap.copyTo(mLeap, alpha);
	result = mLeap / 255;
	imshow("result", result);

	/*Mat background = imread("background.png");
	background.convertTo(background, CV_32FC3);

	multiply(Scalar::all(1.0) - alpha, background, background);
	add(mLeap, background, result);*/

	result = result / 255;

	capture >> img;

	while (true) {
		capture.read(img);

		imshow("image", img);

		if (waitKey(1) >= 0) {
			break;
		}
	}

	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	img.convertTo(img, CV_32FC3);
	img = img / 255;
	resize(result, result, Size(faces[0].height, faces[0].width));
	result.copyTo(img(faces[0]));

	imshow("frame", img);
	waitKey(0);

	return 0;
}


 //get mask for magic leap frame
	 /*GaussianBlur(mLeap, blur, Size(7, 7), 9, 0);
	int hmin = 0, hmax = 173, smin = 18, smax = 255, vmin = 0, vmax = 255;

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	Scalar min(hmin, smin, vmin);
	Scalar max(hmax, smax, vmax);
	cvtColor(blur, mLeapHSV, COLOR_BGR2HSV);
	inRange(mLeapHSV, min, max, alpha);*/

	//view magic leap with transparent background
	/*imshow("Magic Leap", result);
	waitKey(0);*/

	//make a transparent background
	/*Mat background(mLeap.size(), CV_8UC4);
	background = cv::Scalar(255, 255, 255, 0);
	background.convertTo(background, CV_32FC3);
	imwrite("background.png", background);*/