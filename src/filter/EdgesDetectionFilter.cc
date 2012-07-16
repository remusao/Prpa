#include "EdgesDetectionFilter.hh"

int   g_thresh = 100;

EdgesDetectionFilter::EdgesDetectionFilter()
  : filter (/* is_serial */ false)
{
}

void*
EdgesDetectionFilter::operator()(void* tok)
{
  std::pair<IplImage*, IplImage*>* pair
    = static_cast<std::pair<IplImage*, IplImage*>*> (tok);
  IplImage* g_image = pair->first;
  IplImage* g_gray;
  CvMemStorage* g_storage;
  g_storage = cvCreateMemStorage(0);

  CvSeq* contours = 0;
  if (g_image->nChannels == 1)
    g_gray = g_image;
  else
    g_gray = cvCreateImage( cvGetSize( g_image ), IPL_DEPTH_8U, 1 );

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
  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(g_gray, pair->second);
  return pair2;
}

std::string
EdgesDetectionFilter::get_name ()
{
  return "Edges detection filter";
}
