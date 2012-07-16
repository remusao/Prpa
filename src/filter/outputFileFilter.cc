#include "outputFileFilter.hh"

OutputFileFilter::OutputFileFilter()
    : filter(/* is_serial */ true)
{
}


void*
OutputFileFilter::operator()(void* tok)
{
  std::pair<IplImage*, IplImage*>* pair
    = static_cast<std::pair<IplImage*, IplImage*>*> (tok);
  IplImage* img = pair->first;
  if (!img)
    printf ("img null in output\n");
  //We write the image thank's to the writer.
  cvShowImage("PRPA", img);
  cvWaitKey(40);
  return 0;
}

std::string
OutputFileFilter::get_name()
{
    return "Output File Filter";
}
