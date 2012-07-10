#ifndef DILATEFILTER_HH_
# define DILATEFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class DilateFilter : public tbb::filter
{
  public:
    DilateFilter();
    std::string get_name ();
  private:
    void* operator()(void*);
};

#endif
