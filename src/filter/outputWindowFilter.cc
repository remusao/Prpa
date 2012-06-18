#include "outputWindowFilter.hh"

OutputWindowFilter::OutputWindowFilter()
    : filter(true)
{
}


void*
OutputWindowFilter::operator()(void*)
{
    return (void*)0x0;
}

std::string
OutputWindowFilter::get_name()
{
    return "Output Window Filter";
}
