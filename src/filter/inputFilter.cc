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
    //If we want we can show the image.
    return cvRetrieveFrame (capture);
  }
  else
    return 0;
}

std::string
InputFilter::get_name()
{
    return "Input Filter";
}
