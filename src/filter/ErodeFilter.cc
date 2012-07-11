#include "ErodeFilter.hh"

ErodeFilter::ErodeFilter()
  : filter (/* is_serial */ false)
{
}

void*
ErodeFilter::operator()(void* elt)
{
  IplImage* img = static_cast<IplImage*> (elt);
  if (!img)
    printf("img null in canny filter\n");
  IplImage* out;
  if (!cvGetImageCOI(img))
    out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
  else
    out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, cvGetImageCOI(img));
  cvErode(img, out, 0, 5);

  return out;
}

std::string
ErodeFilter::get_name ()
{
  return "Erode filter";
}
