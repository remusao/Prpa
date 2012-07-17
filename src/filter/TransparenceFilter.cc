#include "TransparenceFilter.hh"
#include "string.h"

TransparenceFilter::TransparenceFilter()
  : filter (/* is_serial */ false)
{
}

void*
TransparenceFilter::operator()(void* elt)
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

  float alpha = 0.3f;

  for(int i=0;i<img->imageSize;i++)
  {
     data[i] = (unsigned char)(alpha * (float)img->imageData[i]);
  }
  for(int i=0;i<img2->imageSize;i++)
  {
     data[i] += (unsigned char)((1.0f - alpha) * (float)img2->imageData[i]);
  }
  std::pair<IplImage*, IplImage*>* pair2
    = new std::pair<IplImage*, IplImage*>(out, pair->second);
  return pair2;
}

std::string
TransparenceFilter::get_name ()
{
  return "Transparence filter";
}
