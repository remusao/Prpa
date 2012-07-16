#ifndef FACEDETECTFILTER_HH_
# define FACEDETECTFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class FaceDetectionFilter : public tbb::filter
{
  public:
    FaceDetectionFilter();
    std::string get_name ();
  private:
    void* operator()(void*);
};

#endif
