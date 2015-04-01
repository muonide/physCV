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
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
	//cap.set(CV_CAP_PROP_FOCUS_AUTO,1);
	//cap.set(CV_CAP_PROP_EXPOSURE_AUTO,3);

	Mat src;
	cap >> src;

	Mat grey, edges;
	cvtColor(src, grey, CV_BGR2GRAY);
	Canny(grey, edges, 5, 40, 3);
	//cvtColor(edges, edges, CV_GRAY2BGR); 

	vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180, 1, 0, 0);

	Mat hough;
	hough = Mat::zeros(200,200,CV_32F);

	for (size_t i = 0; i < lines.size(); i++){
		if( lines[i][0] > 0){
		rho = cvRound(lines[i][0]/15);
		theta = cvRound(lines[i][1]*180/CV_PI);
		hough.at<float>(Point(rho,theta)) += 20;

		cout << "Rho is " <<  rho << ", Theta is " << theta << ",pixel is " << hough.at<float>(Point(rho,theta)) << endl;
		
//		hough.at<int>(Point(theta,rho)) += 1;
		}
//		cout << theta << "," << rho << "," << hough.at<float>(theta,rho) << endl;


	}

	cout << hough;
	imwrite("edges.png", edges);
	imwrite("source.png", src);
	imwrite("hough.png", hough);

	return 0;
}


