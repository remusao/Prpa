#include "ErodeFilter.hh"

ErodeFilter::ErodeFilter()
  : filter (/* is_serial */ false)
{
}

void*
ErodeFilter::operator()(void* elt)
{
  std::pair<IplImage*, IplImage*>* pair
    = static_cast<std::pair<IplImage*, IplImage*>*> (elt);
  IplImage* img = pair->first;
  if (!img)
    printf("img null in canny filter\n");
  IplImage* out;
  out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, img->nChannels);
  cvErode(img, out, 0, 5);

  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(out, pair->second);
  return pair2;
}

std::string
ErodeFilter::get_name ()
{
  return "Erode filter";
}
