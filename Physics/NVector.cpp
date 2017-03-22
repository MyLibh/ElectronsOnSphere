#include "NVector.hpp"

double atan_ (double x, double y)
    {
    if (fabs(x) < MIN_NUM_FOR_DIVIDE) return (y > 0)? M_PI_2 : M_PI + M_PI_2;
    double returned = atan (y/x);
    return (x > 0)? returned : returned + M_PI;
    }

double sqr (double x)
    {
    return x*x;
    }
