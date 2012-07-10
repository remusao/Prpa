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
  IplImage* out = 0;
  cvCanny(img, out, 200 * 49, 600 * 49, 7);

  return img;
}

std::string
CannyFilter::get_name ()
{
  return "Canny filter";
}
