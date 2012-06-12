#include <string>
#include "cv.h"
#include "highgui.h"
#include "interpreter/driver.hh"

using namespace cv;


int test()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


int main(int argc, char *argv[])
{
    parsepit::Driver d;

    if (argc == 2)
        d.parse_file(*new std::string(argv[1]));

    return 0;
}
