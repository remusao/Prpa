#include <string>
#include <cstdlib>
#include <iostream>
#include "cv.h"
#include "highgui.h"
#include "driver.hh"
#include "tbb/task_scheduler_init.h"
#include "tbb/pipeline.h"
#include "filter/inputFilter.hh"
#include "filter/outputFileFilter.hh"
#include "filter/CannyFilter.hh"

using namespace cv;

int test(parsepit::Driver& drv, int threads)
{
  tbb::task_scheduler_init init(threads);
  //The pipeline.
  tbb::pipeline pipeline;

  //First we init the inputs and outputs.
  //CvCapture* capture = cvCaptureFromFile(drv.input_get ()->c_str());
  CvCapture* capture = cvCreateCameraCapture(0);

  IplImage* img = 0;
  if (!cvGrabFrame(capture))
  {              // capture a frame 
      printf("Could not grab a frame\n\7");
      exit(0);
  }
  img = cvRetrieveFrame(capture);           // retrieve the captured frame
  cvQueryFrame(capture); // this call is necessary to get correct capture properties
  int frameH    = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
  int frameW    = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
  int fps       = 30;//(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
  int isColor = 1;

  CvVideoWriter* writer = cvCreateVideoWriter(drv.output_get ()->c_str(), CV_FOURCC('P','I','M','1'),
                                 fps, cvSize(frameW, frameH), isColor);
  //We feed the pipeline with filters.
  InputFilter ifilter (capture);
  //Input
  pipeline.add_filter (ifilter);

  //CannyFilter
  CannyFilter canny_filter;
  pipeline.add_filter (canny_filter);

  OutputFileFilter ofilter (writer);
  //Output
  pipeline.add_filter (ofilter);
  //Then we can run the pipeline.
  pipeline.run(threads);

  //We release the inputs and outputs and clear the pipeline.
  pipeline.clear();
  cvReleaseCapture(&capture);
  cvReleaseVideoWriter(&writer);

  return 0;
}


int usage()
{
    std::cout << "Parallel stream processing Usage :" << std::endl;
    std::cout << "./prpa <script_file> [nthread]" << std::endl;
    return 1;
}


int main(int argc, char *argv[])
{
    unsigned nthread = 4;
    if (argc == 1)
        return usage();
    else if (argc == 3)
        nthread = atoi(argv[2]);

    std::cout << nthread << std::endl;
    parsepit::Driver d;

    if (argc >= 2)
        d.parse_file(*new std::string(argv[1]));
    test (d, nthread);

    return 0;
}
