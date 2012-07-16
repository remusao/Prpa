#include "DilateFilter.hh"

DilateFilter::DilateFilter()
  : filter (/* is_serial */ false)
{
}

void*
DilateFilter::operator()(void* elt)
{
  std::pair<IplImage*, IplImage*>* pair
    = static_cast<std::pair<IplImage*, IplImage*>*> (elt);
  IplImage* img = pair->first;
  if (!img)
    printf("img null in dilate filter\n");
  IplImage* out;
  out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, img->nChannels);
  cvDilate(img, out, 0, 5);

  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(out, pair->second);
  return pair2;
}

std::string
DilateFilter::get_name ()
{
  return "Dilate filter";
}
