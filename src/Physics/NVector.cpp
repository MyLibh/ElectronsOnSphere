#include "NVector.hpp"

double atan_ (double x, double y)
    {
    if (fabs(x) < MIN_NUM_FOR_DIVIDE) return (y > 0)? M_PI_2 : M_PI + M_PI_2;
    double returned = atan (y/x);
    return (x > 0)? returned : returned + M_PI;
    }

inline double sqr (double x)
    {
    return x*x;
    }

    //{ base_vector   

base_vector::base_vector (double x1, double y1, double z1) :
    _X (x1),
    _Y (y1),
    _Z (z1)
        {}

double base_vector::getX() const
    {
    return _X;
    }

double base_vector::getY() const
    {
    return _Y;
    }

double base_vector::getZ() const
    {
    return _Z;
    }

    //}

    //{ vec

const vec& vec::operator= (const vec& vec_) 
    {
    _X = vec_._X;
    _Y = vec_._Y;
    _Z = vec_._Z;

    return *this;
    }

vec vec::operator* (double module) const
    {
    return vec (_X*module, _Y*module, _Z*module);
    }

const vec& vec::operator+= (const vec& vec_)
    {
    _X+= vec_._X;
    _Y+= vec_._Y;
    _Z+= vec_._Z;

    return *this;
    }

    //}

    //{ nvec

nvec nvec::operator+ (const vec& vec_) const
    {
    double length = sqrt (sqr(_X + vec_.getX()) + sqr(_Y + vec_.getY()) + sqr(_Z + vec_.getZ()));
    return nvec ((_X + vec_.getX())/length,
                 (_Y + vec_.getY())/length,
                 (_Z + vec_.getZ())/length);
    }

const nvec& nvec::operator= (const nvec& vec_)
    {
    _X = vec_.getX();
    _Y = vec_.getY();
    _Z = vec_.getZ();

    return *this;
    }

    //}
