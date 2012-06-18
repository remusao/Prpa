#include "outputFileFilter.hh"

OutputFileFilter::OutputFileFilter()
    : filter(true)
{
}


void*
OutputFileFilter::operator()(void*)
{
    return (void*)0x0;
}

std::string
OutputFileFilter::get_name()
{
    return "Output File Filter";
}
