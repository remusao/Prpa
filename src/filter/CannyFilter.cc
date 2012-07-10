#include "CannyFilter.hh"

CannyFilter::CannyFilter()
  : filter (/* is_serial */ false)
{
}

void*
CannyFilter::operator()(void* elt)
{
  IplImage* img = static_cast<IplImage*> (elt);
  if (!img)
    printf("img null in canny filter\n");
  IplImage* out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
  cvErode(img, out, 0, 5);

  return out;
}

std::string
CannyFilter::get_name ()
{
  return "Canny filter";
}
