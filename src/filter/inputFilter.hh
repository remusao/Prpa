#ifndef INPUTFILTER_HH_
# define INPUTFILTER_HH_

# include <string>
#include "tbb/pipeline.h"

class InputFilter : public tbb::filter
{
    public:
        InputFilter();
        std::string get_name();
    private:
        void* operator()(void*);
};

#endif /* !INPUTFILTER_HH_ */
