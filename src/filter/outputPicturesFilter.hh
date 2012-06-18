#ifndef OUTPUTPICTURESFILTER_HH_
# define OUTPUTPICTURESFILTER_HH_

# include <string>
#include "tbb/pipeline.h"

class OutputPicturesFilter : public tbb::filter
{
    public:
        OutputPicturesFilter();
        std::string get_name();
    private:
        void* operator()(void*);
};

#endif /* !OUTPUTPICTURESFILTER_HH_ */
