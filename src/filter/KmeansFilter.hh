#ifndef KMEANSFILTER_HH_
# define KMEANSFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class KmeansFilter : public tbb::filter
{
   public:
    KmeansFilter();
    std::string get_name ();
    private:
    void* operator()(void*);
};

#endif /* !KMEANSFILTER_HH_ */
