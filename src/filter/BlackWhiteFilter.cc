#include "BlackWhiteFilter.hh"

BlackWhiteFilter::BlackWhiteFilter()
  : filter (/* is_serial */ false)
{
}

void*
BlackWhiteFilter::operator()(void* elt)
{
  std::pair<IplImage*, IplImage*>* pair
    = static_cast<std::pair<IplImage*, IplImage*>*> (elt);
  IplImage* img = pair->first;
  if (!img)
    printf("img null in canny filter\n");
  IplImage* out;
  if (img->nChannels == 1)
    return img;
  out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
  cvCvtColor(img, out, CV_BGR2GRAY);
  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(out, pair->second);
  return pair2;
}

std::string
BlackWhiteFilter::get_name ()
{
  return "BlackWhite filter";
}
