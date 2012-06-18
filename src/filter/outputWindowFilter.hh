#ifndef OUTPUTWINDOWFILTER_HH_
# define OUTPUTWINDOWFILTER_HH_

# include <string>
#include "tbb/pipeline.h"

class OutputWindowFilter : public tbb::filter
{
    public:
        OutputWindowFilter();
        std::string get_name();
    private:
        void* operator()(void*);
};

#endif /* !OUTPUTWINDOWFILTER_HH_ */
