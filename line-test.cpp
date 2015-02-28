#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main(int, char**)
{

VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
 Mat src;
 cap >> src;
 
    Mat dst, cdst, ddst;
    cvtColor(src, dst, CV_BGR2GRAY)
    Canny(dst, cdst, 50, 200, 3); 
    cvtColor(cdst, ddst, CV_GRAY2BGR); 
 
    //vector<Vec2f> lines;    //define vector class 2x1 floating point precision
    // detect lines
    //HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );
 // draw lines
 //   for( size_t i = 0; i < lines.size(); i++ )
 //   {
 //       float rho = lines[i][0], theta = lines[i][1];
 //       Point pt1, pt2;
 //       double a = cos(theta), b = sin(theta);
 //       double x0 = a*rho, y0 = b*rho;
 //       pt1.x = cvRound(x0 + 1000*(-b));
 //       pt1.y = cvRound(y0 + 1000*(a));
 //       pt2.x = cvRound(x0 - 1000*(-b));
 //       pt2.y = cvRound(y0 - 1000*(a));
 //       line( ddst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
 //   }
 vector<Vec4i> lines;  //define vector class for lines, a 4xn matrix of integers?  
 //vector<Vec4f> lines;  //define vector class for lines, a 4xn matrix of floats
  HoughLinesP(cdst, lines, 1, CV_PI/180, 50, 50, 10 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];   //pick a 4x1 array out of the lines matrix
    line( ddst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);   
    //draw lines onto ddst that connects the poinnts defined in that 4x1 array, Scalar(0,0,255) defines the color red
  }
 
    imwrite("source.png", src); //write original capture
    imwrite("edges.png", cdst); //write Canny image
    imwrite("lines.png", ddst): //write Canny + lines
    waitKey();
    return 0;
}

