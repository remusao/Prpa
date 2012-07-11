#include "DilateFilter.hh"

DilateFilter::DilateFilter()
  : filter (/* is_serial */ false)
{
}

void*
DilateFilter::operator()(void* elt)
{
  IplImage* img = static_cast<IplImage*> (elt);
  if (!img)
    printf("img null in dilate filter\n");
  IplImage* out;
  if (!cvGetImageCOI(img))
    out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
  else
    out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, cvGetImageCOI(img));
  cvDilate(img, out, 0, 5);

  return out;
}

std::string
DilateFilter::get_name ()
{
  return "Dilate filter";
}
