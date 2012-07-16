#ifndef TRANSPARENCEFILTER_HH_
# define TRANSPARENCEFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class TransparenceFilter : public tbb::filter
{
  public:
    TransparenceFilter();
    std::string get_name ();
  private:
    void* operator()(void*);
};

#endif /* !TRANSPARENCEFILTER_HH_ */
