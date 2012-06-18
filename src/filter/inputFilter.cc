#include "inputFilter.hh"

InputFilter::InputFilter()
    : filter(true)
{
}


void*
InputFilter::operator()(void*)
{
    return (void*)0x0;
}

std::string
InputFilter::get_name()
{
    return "Input Filter";
}
