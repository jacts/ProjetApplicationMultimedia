#include <opencv2\opencv.hpp>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

String Window = "Window";
String image;
int action;
Mat modified_image;
String imageName;
Mat img;
double alpha;




Mat3b canvas;
string buttonText("Click me!");
string winName = "My image editor";
int bright;

Rect button;


void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (button.contains(Point(x, y)))
		{
			//erode(canvas, canvas, Mat(), Point(-1, -1), 1, BORDER_CONSTANT, morphologyDefaultBorderValue());
			cout << "Clicked!" << endl;
			rectangle(canvas(button), button, Scalar(0, 0, 255), 2);
		}
	}
	if (event == EVENT_LBUTTONUP)
	{
		rectangle(canvas, button, Scalar(200, 200, 200), 2);
	}

	imshow(winName, canvas);
	waitKey(1);
}

int main()
{

	cout << "Choose the image to display" << endl;
	cin >> imageName;

	img = imread(imageName, 1);

	if (img.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// Your button
	button = Rect(0, 0, img.cols, 50);

	// The canvas
	canvas = Mat3b(img.rows + button.height, img.cols, Vec3b(0, 0, 0));

	// Draw the button
	canvas(button) = Vec3b(200, 200, 200);
	putText(canvas(button), buttonText, Point(button.width*0.35, button.height*0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));

	// Draw the image
	img.copyTo(canvas(Rect(0, button.height, img.cols, img.rows)));



	// Setup callback function
	namedWindow(winName);

	setMouseCallback(winName, callBackFunc, &img);

	//Create trackbar to change brightness
	int iSliderValue1 = 50;
	createTrackbar("Brightness", winName, &iSliderValue1, 100);

	//Create trackbar to change contrast
	int iSliderValue2 = 50;
	createTrackbar("Contrast", winName, &iSliderValue2, 100);

	Mat clearedImage = img.clone();

	while (true)
	{
		//Change the brightness and contrast of the image 
		Mat dst;
		int iBrightness = iSliderValue1 - 50;
		double dContrast = iSliderValue2 / 50.0;
		canvas.convertTo(canvas, -1, dContrast, iBrightness);

		//show the brightness and contrast adjusted image
		imshow(winName, canvas);

		// Wait until user press some key for 50ms
		int iKey = waitKey(50);

		//if user press 'ESC' key
		if (iKey == 27)
		{
			break;
		}
		if (iKey == 99)
		{
			iSliderValue2 = 50;
			clearedImage.copyTo(canvas);
		}
	}

	//if (action == 1) {
	//	erode(img, modified_image, Mat(), Point(-1, -1), 1, BORDER_CONSTANT, morphologyDefaultBorderValue());
	//}
	//else if (action == 2) {
	//	dilate(img, modified_image, Mat(), Point(-1, -1), 1, BORDER_CONSTANT, morphologyDefaultBorderValue());
	//}
	//else if (action == 3) {
	//	resize(img, modified_image, Size(round(0.6*img.cols), round(0.6*img.rows)), 0.6, 0.6, INTER_LINEAR);
	//}

	//else if (action == 5) {
	//	dilate(img, modified_image, Mat(), Point(-1, -1), 1, BORDER_CONSTANT, morphologyDefaultBorderValue());
	//}
	//else if (action == 6) {
	//	edges = Canny(img, 100, 200);
	//}


	imshow(winName, canvas);
	waitKey();

	return 0;
}