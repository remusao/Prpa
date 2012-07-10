#ifndef OUTPUTFILEFILTER_HH_
# define OUTPUTFILEFILTER_HH_

# include <string>
# include "tbb/pipeline.h"
# include "cv.h"
# include "highgui.h"

class OutputFileFilter : public tbb::filter
{
    public:
        OutputFileFilter(CvVideoWriter*);
        std::string get_name();
    private:
        void* operator()(void*);
        CvVideoWriter* writer;
};

#endif /* !OUTPUTFILEFILTER_HH_ */
