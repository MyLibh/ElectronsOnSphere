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

    //{ vec

vec::vec () :
    _X (0),
    _Y (0),
    _Z (0)
        {}

vec::vec (double x1, double y1, double z1) :
    _X (x1),
    _Y (y1),
    _Z (z1)
        {}

void vec::operator= (vec vec_)
    {
    _X = vec_._X;
    _Y = vec_._Y;
    _Z = vec_._Z;
    }

vec vec::operator* (double module)
    {
    return vec (_X*module, _Y*module, _Z*module);
    }

void vec::operator+= (vec vec_)
    {
    _X+= vec_._X;
    _Y+= vec_._Y;
    _Z+= vec_._Z;
    }

double vec::getX()
    {
    return _X;
    }

double vec::getY()
    {
    return _Y;
    }

double vec::getZ()
    {
    return _Z;
    }

    //}

    //{ nvec

nvec::nvec (double x1, double y1, double z1) :
    _X (x1),
    _Y (y1),
    _Z (z1)
    {}

nvec::nvec () :
    _X (0),
    _Y (0),
    _Z (0)
    {}

nvec nvec::operator+ (vec vec_)
    {
    double length = sqrt (sqr(_X + vec_.getX()) + sqr(_Y + vec_.getY()) + sqr(_Z + vec_.getZ()));
    return nvec ((_X + vec_.getX())/length,
                 (_Y + vec_.getY())/length,
                 (_Z + vec_.getZ())/length);
    }

void nvec::operator= (nvec vec_)
    {
    _X = vec_.getX();
    _Y = vec_.getY();
    _Z = vec_.getZ();
    }

double nvec::getX () const
    {
    return _X;
    }

double nvec::getY () const
    {
    return _Y;
    }

double nvec::getZ () const
    {
    return _Z;
    }

    //}
