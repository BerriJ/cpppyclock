#ifndef CHAMELEON
#define CHAMELEON

#include <pybind11/pybind11.h>

namespace chameleon
{
    inline void warn(std::string msg)
    {
        pybind11::print(msg.c_str());
    }
};

#endif