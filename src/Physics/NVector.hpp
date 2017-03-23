#ifndef __NVECTOR_H_INCLUDED__ //{
#define __NVECTOR_H_INCLUDED__

#include "..\Includes.hpp"

#define MIN_NUM_FOR_DIVIDE 0.000001

double atan_ (double x, double y);

double sqr (double);

class vec final
    {
    public:
        double _X, _Y, _Z;

        vec () :
        _X (0),
        _Y (0),
        _Z (0)
            {}

        vec (double x1, double y1, double z1) :
        _X (x1),
        _Y (y1),
        _Z (z1)
            {}

        void operator= (vec vec_)
            {
            _X = vec_._X;
            _Y = vec_._Y;
            _Z = vec_._Z;
            }

        void operator*= (double module)
            {
            _X*= module;
            _Y*= module;
            _Z*= module;
            }

        void operator+= (vec vec_)
            {
            _X+= vec_._X;
            _Y+= vec_._Y;
            _Z+= vec_._Z;
            }
    };

class nvec final
    {
    private:
        double _X, _Y, _Z;

    public:
        nvec (double x1, double y1, double z1) :
            _X (x1),
            _Y (y1),
            _Z (z1)
            {}

        nvec ():
            _X (0),
            _Y (0),
            _Z (0)
            {}

        nvec operator+ (vec vec_)
            {
            double length = sqrt (sqr(_X + vec_._X) + sqr(_Y + vec_._Y) + sqr(_Z + vec_._Z));
            return nvec ((_X + vec_._X)/length,
                         (_Y + vec_._Y)/length,
                         (_Z + vec_._Z)/length);
            }

        void operator= (nvec vec_)
            {
            _X = vec_._X;
            _Y = vec_._Y;
            _Z = vec_._Z;
            }

        double getX () const
            {
            return _X;
            }

        double getY () const
            {
            return _Y;
            }

        double getZ () const
            {
            return _Z;
            }

    friend vec Strength (nvec, nvec);
    };

#endif // __NVECTOR_H_INCLUDED__ }
