#include "revert.hh"


Revert::Revert()
    : filter(true)
{
}


void*
Revert::operator()(void*)
{
    return (void*)0x0;
}

std::string
Revert::get_name()
{
    return "toto";
}
