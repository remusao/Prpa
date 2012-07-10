#include "CannyFilter.hh"

CannyFilter::CannyFilter()
  : filter (/* is_serial */ false)
{
}

void*
CannyFilter::operator()(void* elt)
{
  IplImage* img = static_cast<IplImage*> (elt);
  IplImage* out = 0;
  cvCanny(img, out, 200 * 49, 600 * 49, 7);
  return out;
}

std::string
CannyFilter::get_name ()
{
  return "Canny filter";
}
