#include "outputFileFilter.hh"

OutputFileFilter::OutputFileFilter()
    : filter(/* is_serial */ true)
{
}


void*
OutputFileFilter::operator()(void* tok)
{
  IplImage* img = static_cast<IplImage*> (tok);
  if (!img)
    printf ("img null in output\n");
  //We write the image thank's to the writer.
  cvShowImage("PRPA", tok);
  return 0;
}

std::string
OutputFileFilter::get_name()
{
    return "Output File Filter";
}
