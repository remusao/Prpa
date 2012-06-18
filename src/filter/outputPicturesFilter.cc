#include "outputPicturesFilter.hh"

OutputPicturesFilter::OutputPicturesFilter()
    : filter(true)
{
}


void*
OutputPicturesFilter::operator()(void*)
{
    return (void*)0x0;
}

std::string
OutputPicturesFilter::get_name()
{
    return "Output Pictures Filter";
}
