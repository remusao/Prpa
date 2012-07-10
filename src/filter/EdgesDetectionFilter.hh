#ifndef EDGESDETECTIONFILTER_HH_
# define EDGESDETECTIONFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class EdgesDetectionFilter : public tbb::filter
{
  public:
    EdgesDetectionFilter ();
    std::string get_name ();
  private:
    void* operator()(void*);
    CvMemStorage* g_storage;
};

#endif
