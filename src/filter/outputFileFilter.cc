#include "outputFileFilter.hh"

OutputFileFilter::OutputFileFilter(CvVideoWriter* wri)
    : filter(/* is_serial */ true),
    writer (wri)
{
}


void*
OutputFileFilter::operator()(void* tok)
{
  IplImage* img = static_cast<IplImage*> (tok);
  //We write the image thank's to the writer.
  cvWriteFrame(writer, img);
  return 0;
}

std::string
OutputFileFilter::get_name()
{
    return "Output File Filter";
}
