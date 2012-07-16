#ifndef MIXFILTER_HH_
# define MIXFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class MixFilter : public tbb::filter
{
  public:
    MixFilter();
    std::string get_name ();
  private:
    void* operator()(void*);
};

#endif /* !MIXFILTER_HH_ */
