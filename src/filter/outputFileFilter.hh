#ifndef OUTPUTFILEFILTER_HH_
# define OUTPUTFILEFILTER_HH_

# include <string>
#include "tbb/pipeline.h"

class OutputFileFilter : public tbb::filter
{
    public:
        OutputFileFilter();
        std::string get_name();
    private:
        void* operator()(void*);
};

#endif /* !OUTPUTFILEFILTER_HH_ */
