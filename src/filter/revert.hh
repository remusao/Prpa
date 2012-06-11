#ifndef REVERT_HH_
# define REVERT_HH_

# include <string>
#include "tbb/pipeline.h"

class Revert : public tbb::filter
{
    public:
        Revert();
        std::string get_name();
    private:
        void* operator()(void*);
};

#endif /* !REVERT_HH_ */
