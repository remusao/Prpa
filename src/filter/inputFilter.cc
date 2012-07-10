#include "inputFilter.hh"

InputFilter::InputFilter(CvCapture* cap)
    : filter(/* is_serial */ true),
    capture (cap)
{
}


void*
InputFilter::operator()(void* elt)
{
  if (cvGrabFrame (capture))
  {
    IplImage* img = cvRetrieveFrame (capture);
    if (!img)
      printf("img is null in input filter.\n");
    //If we want we can show the image.
    return img;
  }
  else
    return 0;
}

std::string
InputFilter::get_name()
{
    return "Input Filter";
}
