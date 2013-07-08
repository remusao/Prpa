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
#include "filter/ErodeFilter.hh"
#include "filter/DilateFilter.hh"
#include "filter/EdgesDetectionFilter.hh"
#include "filter/BlackWhiteFilter.hh"
#include "filter/FaceDetectionFilter.hh"
#include "filter/MixFilter.hh"
#include "filter/TransparenceFilter.hh"
#include "filter/KmeansFilter.hh"

using namespace cv;


void set_filters(tbb::pipeline* pipeline, parsepit::Driver& drv)
{
    for (const auto& filter: drv.filters_get())
    {
        if (filter->compare("Erode") == 0)
            pipeline->add_filter(*new ErodeFilter());
        else if (filter->compare("Kmeans") == 0)
            pipeline->add_filter(*new KmeansFilter());
        else if (filter->compare("Dilate") == 0)
            pipeline->add_filter(*new DilateFilter());
        else if (filter->compare("EdgeDetection") == 0)
            pipeline->add_filter(*new EdgesDetectionFilter());
        else if (filter->compare("BlackWhite") == 0)
            pipeline->add_filter(*new BlackWhiteFilter());
        else if (filter->compare("EyeDetect") == 0)
            pipeline->add_filter(*new FaceDetectionFilter("/usr/share/OpenCV/haarcascades/haarcascade_eye.xml"));
        else if (filter->compare("FaceDetect") == 0)
            pipeline->add_filter(*new FaceDetectionFilter("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"));
        else if (filter->compare("GlassesDetect") == 0)
            pipeline->add_filter(*new FaceDetectionFilter("/usr/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml"));
        else if (filter->compare("MouthDetect") == 0)
            pipeline->add_filter(*new FaceDetectionFilter("/usr/share/OpenCV/haarcascades/haarcascade_mcs_mouth.xml"));
        else if (filter->compare("NoseDetect") == 0)
            pipeline->add_filter(*new FaceDetectionFilter("/usr/share/OpenCV/haarcascades/haarcascade_mcs_nose.xml"));
        else if (filter->compare("BodyDetect") == 0)
            pipeline->add_filter(*new FaceDetectionFilter("/usr/share/OpenCV/haarcascades/haarcascade_mcs_upperbody.xml"));
        else if (drv.fusion_get() && filter->compare("Mixage") == 0)
            pipeline->add_filter(*new MixFilter());
        else if (drv.fusion_get () && filter->compare("Transparence") == 0)
            pipeline->add_filter(*new TransparenceFilter());
    }
}

int test(parsepit::Driver& drv, int threads)
{
  tbb::task_scheduler_init init(threads);
  //The pipeline.
  tbb::pipeline pipeline;

  if (!drv.input_get() || !drv.output_get())
  {
    printf("Input or output not specified.\n");
    exit(0);
  }

  //First we init the inputs and outputs.
  CvCapture* capture;
  if (drv.input_get()->compare("WEBCAM") == 0)
    capture = cvCreateCameraCapture(0);
  else
    capture = cvCaptureFromFile(drv.input_get ()->c_str());

  CvCapture* capture2 = 0;
  if (drv.fusion_get () && drv.fusion_get ()->compare("WEBCAM") == 0)
    capture2 = cvCreateCameraCapture(0);
  else if (drv.fusion_get ())
    capture2 = cvCaptureFromFile(drv.fusion_get ()->c_str ());

  //IplImage* img = 0;
  if (!cvGrabFrame(capture))
  {              // capture a frame 
      printf("Could not grab a frame from capture1\n\7");
      exit(0);
  }
  //IplImage* img2 = 0;
  if (capture2 && !cvGrabFrame(capture2))
  {              // capture a frame 
      printf("Could not grab a frame from capture2\n\7");
      exit(0);
  }

  std::pair<CvCapture*, CvCapture*> pair_cap
    /*= new std::pair<CvCapture*, CvCapture*>*/ (capture, capture2);

  //We feed the pipeline with filters.
  InputFilter ifilter (pair_cap);
  //Input
  pipeline.add_filter (ifilter);

  set_filters(&pipeline, drv);

  // Init windows
  cvNamedWindow("PRPA", 1);
  OutputFileFilter ofilter;
  //Output
  pipeline.add_filter (ofilter);
  //Then we can run the pipeline.
  pipeline.run(threads);

  //We release the inputs and outputs and clear the pipeline.
  pipeline.clear();
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
