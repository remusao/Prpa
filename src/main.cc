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
  CvCapture* capture = cvCaptureFromFile(drv.input_get ()->c_str());

  IplImage* img = 0;
  if (!cvGrabFrame(capture))
  {              // capture a frame 
      printf("Could not grab a frame\n\7");
      exit(0);
  }
  //img=cvRetrieveFrame(capture);           // retrieve the captured frame

  //We feed the pipeline with filters.
  /*InputFilter ifilter (capture);
  //Input
  pipeline.add_filter (ifilter);

  //CannyFilter
  CannyFilter canny_filter;
  //pipeline.add_filter (canny_filter);

  OutputFileFilter ofilter;
  //Output
  pipeline.add_filter (ofilter);
  //Then we can run the pipeline.
  pipeline.run(threads);

  //We release the inputs and outputs and clear the pipeline.
  pipeline.clear();
  */while (cvGrabFrame(capture))
  {
    IplImage* tmp = 0;
    cvCanny(cvRetrieveFrame(capture), tmp, 200 * 49, 600 * 49, 7);
    cvShowImage("test", tmp);
    cvWaitKey(20);
    //cvWriteFrame(writer, cvQueryFrame(capture));
  }
  cvReleaseCapture(&capture);

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

    std::cout << argc << " " << nthread << std::endl;
    parsepit::Driver d;

    if (argc >= 2)
        d.parse_file(*new std::string(argv[1]));

    test (d, nthread);

    return 0;
}
