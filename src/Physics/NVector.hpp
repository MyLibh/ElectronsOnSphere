#ifndef __NVECTOR_H_INCLUDED__ //{
#define __NVECTOR_H_INCLUDED__

#include "..\Includes.hpp"

#define MIN_NUM_FOR_DIVIDE 0.000001

double atan_ (double x, double y);

inline double sqr (double);

class base_vector 
    {
    protected:
        double _X, _Y, _Z;

    public:
        base_vector (double x1, double y1, double z1);
        
        double getX () const;
        double getY () const;
        double getZ () const;
    };

class vec final : public base_vector
    {
    public:
        vec (double x = 0, double y = 0, double z = 0) : 
            base_vector(x, y, z) 
            { }

        const vec& operator= (const vec& vec_);
        vec operator* (double module) const;
        const vec& operator+= (const vec& vec_);
    };

class nvec final : public base_vector
    {
    public:
        nvec (double x = 0, double y = 0, double z = 0) : 
            base_vector(x, y, z) 
            { }

        nvec operator+ (const vec& vec_) const;
        const nvec& operator= (const nvec& vec_);
    };

typedef std::vector<nvec> nvector;
typedef const nvector& crnvector;

#endif // __NVECTOR_H_INCLUDED__ }
