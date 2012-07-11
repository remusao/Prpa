#include "BlackWhiteFilter.hh"

BlackWhiteFilter::BlackWhiteFilter()
  : filter (/* is_serial */ false)
{
}

void*
BlackWhiteFilter::operator()(void* elt)
{
  IplImage* img = static_cast<IplImage*> (elt);
  if (!img)
    printf("img null in canny filter\n");
  IplImage* out;
  out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
  cvCvtColor(img, out, CV_BGR2GRAY);

  return out;
}

std::string
BlackWhiteFilter::get_name ()
{
  return "BlackWhite filter";
}
