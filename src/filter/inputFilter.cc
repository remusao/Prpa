#include "inputFilter.hh"

InputFilter::InputFilter(std::pair<CvCapture*, CvCapture*>& pair_cap)
    : filter(/* is_serial */ true),
      capture (pair_cap.first),
      capture2 (pair_cap.second)
{
}


void*
InputFilter::operator()(void* elt)
{
  if (cvGrabFrame (capture) && capture2 && cvGrabFrame(capture2))
  {
    IplImage* img = cvRetrieveFrame (capture);
    if (!img)
      printf("img is null in input filter.\n");
    //If we want we can show the image.
    IplImage* img2 = cvRetrieveFrame (capture2);
    if (!img2)
      printf("img2 is null in input filter.\n");
    std::pair<IplImage*, IplImage*>* pair
      = new std::pair<IplImage*, IplImage*>(img, img2);
    //If we want we can show the image.
    return pair;
  }
  else if (cvGrabFrame(capture))
  {
    IplImage* img = cvRetrieveFrame (capture);
    if (!img)
      printf("img is null in input filter.\n");
    std::pair<IplImage*, IplImage*>* pair
      = new std::pair<IplImage*, IplImage*>(img, 0);
    //If we want we can show the image.
    return pair;
  }
  else
    return 0;
}

std::string
InputFilter::get_name()
{
    return "Input Filter";
}
