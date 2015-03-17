#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int rho = 0;
int theta = 0;

int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()){  // check if we succeeded
		return -1;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
	//cap.set(CV_CAP_PROP_FOCUS_AUTO,1);
	//cap.set(CV_CAP_PROP_EXPOSURE_AUTO,3);

	Mat src;
	cap >> src;

	Mat grey, edges;
	//    GaussianBlur(src, blur, Size(7,7), 2.0, 2.0);
	cvtColor(src, grey, CV_BGR2GRAY);
	Canny(grey, edges, 100, 200, 3);
	//cvtColor(edges, edges, CV_GRAY2BGR); 

	vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180, 120, 0, 0);

	Mat hough(800, 600);

	for (size_t i = 0; i < lines.size(); i++){

		rho = cvRound(lines[i][0]);
		theta = cvRound(600 * lines[i][1] / CV_PI);

		hough.row(rho) += 1;
		hough.column(theta) += 1;

	}


	//    imwrite("corners.png", src);
	//	imwrite("blur.png", blur);
	imwrite("edges.png", edges);
	imwrite("source.png", src);
	imwrite("hough.png", hough);

	// waitKey();

	return 0;
}


