#ifndef CANNYFILTER_HH_
# define CANNYFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class CannyFilter : public tbb::filter
{
  public:
    CannyFilter();
    std::string get_name ();
  private:
    void* operator()(void*);
};

#endif /* !CANNYFILTER_HH_ */
