#include "MixFilter.hh"

MixFilter::MixFilter()
  : filter (/* is_serial */ false)
{
}

void*
MixFilter::operator()(void* elt)
{
  std::pair<IplImage*, IplImage*>* pair
    = static_cast<std::pair<IplImage*, IplImage*>*> (elt);
  IplImage* img = pair->first;
  IplImage* img2 = pair->second;
  if (!img || !img2)
    printf("img null in canny filter\n");
  IplImage* out;
  out = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, img2->nChannels);

  char* data = out->imageData;
  int height = out->height;
  int width = out->width;
  int step = out->widthStep;
  int channels = out->nChannels;
for (int i = 0; i < img->imageSize; i++) 
     data[i] = 255 - img2->imageData[i];
  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(out, pair->second);
  return pair2;
}

std::string
MixFilter::get_name ()
{
  return "Mix filter";
}
