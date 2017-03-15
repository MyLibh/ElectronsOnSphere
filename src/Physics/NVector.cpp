// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "NVector.hpp"

double atan_ (double x, double y)
    {
    if (fabs(x) < MIN_NUM_FOR_DIVIDE) return (y > 0)? M_PI_2 : M_PI + M_PI_2;
    double returned = atan (y/x);
    return (x > 0)? returned : returned + M_PI;
    }
