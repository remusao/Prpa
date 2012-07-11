#ifndef BLACKWHITEFILTER_HH_
# define BLACKWHITEFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class BlackWhiteFilter : public tbb::filter
{
  public:
    BlackWhiteFilter();
    std::string get_name ();
  private:
    void* operator()(void*);
};

#endif
