#ifndef __NVECTOR_H_INCLUDED__ //{
#define __NVECTOR_H_INCLUDED__

#include "..\Includes.hpp"

#define MIN_NUM_FOR_DIVIDE 0.000001

double atan_ (double x, double y);

double sqr (double);

class vec final
    {
    private:
        double _X, _Y, _Z;

    public:
        vec ();
        vec (double x1, double y1, double z1);

        void operator= (vec vec_);
        vec operator* (double module);
        void operator+= (vec vec_);

        double getX();
        double getY();
        double getZ();
    };

class nvec final
    {
    private:
        double _X, _Y, _Z;

    public:
        nvec (double x1, double y1, double z1);
        nvec ();

        nvec operator+ (vec vec_);
        void operator= (nvec vec_);

        double getX () const;
        double getY () const;
        double getZ () const;
    };

#endif // __NVECTOR_H_INCLUDED__ }
