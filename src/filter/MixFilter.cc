#include "MixFilter.hh"
#include "string.h"

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
  out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, img->nChannels);

  //int height = img->height;
  //int width = img->width;
  //int channels = img->nChannels;
  //int step = img->widthStep;
  unsigned char* data = reinterpret_cast<unsigned char*>(out->imageData);

  //std::cout << height << " " << width << " " << channels << " " << step << " " << img->imageSize << std::endl;
  //std::cout << out->height << " " << out->width << " " << out->nChannels << " " << out->widthStep << " " << out->imageSize << std::endl;

  for(int i=0;i<img->imageSize;i++)
  {
     data[i] = img->imageData[i];
  }
  for(int i=0;i<img2->imageSize;i+=3)
  {
     data[i] = img2->imageData[i];
  }
  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(out, pair->second);
  return pair2;
}

std::string
MixFilter::get_name ()
{
  return "Mix filter";
}
