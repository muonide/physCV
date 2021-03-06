//http://stackoverflow.com/questions/10533233/opencv-c-obj-c-advanced-square-detection


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Point2f computeIntersect(Vec2f line1, Vec2f line2);
vector<Point2f> lineToPointPair(Vec2f line);
bool acceptLinePair(Vec2f line1, Vec2f line2, float minTheta);

int main(int argc, char* argv[])
{
   
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
cap.set(CV_CAP_PROP_FRAME_WIDTH=800);
cap.set(CV_CAP_PROP_FRAME_HEIGHT=600);
 
 int framerate = 15;
 
int frame_width=   cap.get(CV_CAP_PROP_FRAME_WIDTH);
   int frame_height=   cap.get(CV_CAP_PROP_FRAME_HEIGHT);
   VideoWriter video("out.avi",CV_FOURCC('M','J','P','G'),framerate, Size(frame_width,frame_height),true);

   Mat src;
 
 
 
for(;;)   //setup number of captures...maybe make this a while?  need to deal with fps issue?
[

 cap >> src;
 
    Mat dst, grey;
    cvtColor(src, grey, CV_BGR2GRAY);
    Canny(grey, edges, 50, 200, 3); 
    
    vector<Vec2f> lines;
    HoughLines( edges, lines, 1, CV_PI/90, 50, 0, 0 );

    // compute the intersection from the lines detected...
    vector<Point2f> intersections;
    for( size_t i = 0; i < lines.size(); i++ )
    {
        for(size_t j = 0; j < lines.size(); j++)
        {
            Vec2f line1 = lines[i];
            Vec2f line2 = lines[j];
            if(acceptLinePair(line1, line2, CV_PI / 32))  //line pair...
            {
                Point2f intersection = computeIntersect(line1, line2);
                intersections.push_back(intersection);
            }
        }

    }

    if(intersections.size() > 0)
    {
        vector<Point2f>::iterator i;
        for(i = intersections.begin(); i != intersections.end(); ++i)
        {
        //    cout << "Intersection is " << i->x << ", " << i->y << endl;
            circle(src, *i, 1, Scalar(0, 255, 0), 3);
        }
    }
   	
   	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, gray->rows/4, 200, 100 );
    
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // draw the circle center
         circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
    }
   	
   	for( i = 0 ; i < intersection.size() ; i++){
   	cout << "X" << i << "=" << intersection[i][0] << " and Y" << i << "=" << intersection[i][1]; 
   	}
   	for (i = 0 ; i < circles.size() ; i++){
   	cout << "Center X=" << circles[i][0] << " and Center Y=" << circles[i][1]; 
   	}
	 video.write(src);
       imshow( "Frame", src );  //live feed...
       char c = (char)waitKey(33);
       if( c == 27 ) break;
]
    return 0;
}

bool acceptLinePair(Vec2f line1, Vec2f line2, float minTheta)
{
    float theta1 = line1[1], theta2 = line2[1];

    if(theta1 < minTheta)
    {
        theta1 += CV_PI; // dealing with 0 and 180 ambiguities...
    }

    if(theta2 < minTheta)
    {
        theta2 += CV_PI; // dealing with 0 and 180 ambiguities...
    }

    return abs(theta1 - theta2) > minTheta;
}

// the long nasty wikipedia line-intersection equation...bleh...
Point2f computeIntersect(Vec2f line1, Vec2f line2)
{
    vector<Point2f> p1 = lineToPointPair(line1);
    vector<Point2f> p2 = lineToPointPair(line2);

    float denom = (p1[0].x - p1[1].x)*(p2[0].y - p2[1].y) - (p1[0].y - p1[1].y)*(p2[0].x - p2[1].x);
    Point2f intersect(((p1[0].x*p1[1].y - p1[0].y*p1[1].x)*(p2[0].x - p2[1].x) -
                       (p1[0].x - p1[1].x)*(p2[0].x*p2[1].y - p2[0].y*p2[1].x)) / denom,
                      ((p1[0].x*p1[1].y - p1[0].y*p1[1].x)*(p2[0].y - p2[1].y) -
                       (p1[0].y - p1[1].y)*(p2[0].x*p2[1].y - p2[0].y*p2[1].x)) / denom);

    return intersect;
}

vector<Point2f> lineToPointPair(Vec2f line)
{
    vector<Point2f> points;

    float r = line[0], t = line[1];
    double cos_t = cos(t), sin_t = sin(t);
    double x0 = r*cos_t, y0 = r*sin_t;
    double alpha = 1000;

    points.push_back(Point2f(x0 + alpha*(-sin_t), y0 + alpha*cos_t));
    points.push_back(Point2f(x0 - alpha*(-sin_t), y0 - alpha*cos_t));

    return points;
}
