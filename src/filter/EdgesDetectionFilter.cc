#include "EdgesDetectionFilter.hh"

int   g_thresh = 100;

EdgesDetectionFilter::EdgesDetectionFilter()
  : filter (/* is_serial */ false)
{
}

void*
EdgesDetectionFilter::operator()(void* tok)
{
  IplImage* g_image = static_cast<IplImage*>(tok);
  IplImage* g_gray;
  CvMemStorage* g_storage;
  g_gray = cvCreateImage( cvGetSize( g_image ), IPL_DEPTH_8U, 1 );
  g_storage = cvCreateMemStorage(0);

  CvSeq* contours = 0;
  cvCvtColor( g_image, g_gray, CV_BGR2GRAY );
  cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_BINARY );
  cvFindContours( g_gray, g_storage, &contours );
  cvZero( g_gray );
  if( contours ){
    cvDrawContours(
        g_gray,
        contours,
        cvScalarAll(255),
        cvScalarAll(255),
        100 );
  }
  cvClearMemStorage( g_storage );
  return g_gray;
}

std::string
EdgesDetectionFilter::get_name ()
{
  return "Edges detection filter";
}
