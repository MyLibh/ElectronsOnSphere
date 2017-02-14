#ifndef __NVECTOR_H_INCLUDED__ //{
#define __NVECTOR_H_INCLUDED__

#include "..\Includes.hpp"

#define MIN_NUM_FOR_DIVIDE 0.000001

double atan_ (double x, double y);

struct ftan
    {
    double tan;
    bool half;
    void Set (double x, double y)
        {
        half = (x > 0)? 0:1;
        tan = (fabs(y) -  MIN_NUM_FOR_DIVIDE < 0)? 0:(y/x);
        }
    };

class vec final
    {
    public:
        double x, y;

        vec () :
        x (0),
        y (0)
            {}

        vec (ftan tan1) :
        x (sqrt (1/(1 + tan1.tan*tan1.tan)) * ((tan1.half - 0.5 < 0)? 1:-1)),
        y (sqrt (tan1.tan*tan1.tan/(1 + tan1.tan*tan1.tan)) * (((tan1.half - 0.5)*tan1.tan < 0)? 1:-1))
            {}

        vec (double alf) :
        x (cos(alf)),
        y (sin(alf))
            {}

        vec (double x, double y) :
        x (x),
        y (y)
            {}

        void operator= (ftan tan1)
            {
            x = sqrt (1/(1 + tan1.tan*tan1.tan)) * ((tan1.half - 0.5 < 0)? 1:-1);
            y = sqrt (tan1.tan*tan1.tan/(1 + tan1.tan*tan1.tan)) * (((tan1.half - 0.5)*tan1.tan < 0)? 1:-1);
            }

        void operator= (vec vec_)
            {
            x = vec_.x;
            y = vec_.y;
            }

        void operator*= (double module)
            {
            x *= module;
            y *= module;
            }

        void operator+= (vec vec_)
            {
            x += vec_.x;
            y += vec_.y;
            }
    };

class nvec final
    {
    private:
        double nx, ny;

    public:
        nvec (double x, double y) :
            nx (x),
            ny (y)
            {}

        nvec (double alf) :
            nx (cos(alf)),
            ny (sin(alf))
            {}

        nvec ():
            nx (0),
            ny (0)
            {}

        vec strangth (nvec over)
            {
            double module = ((nx - over.nx)*(nx - over.nx) + (ny - over.ny)*(ny - over.ny));
            vec vec_ ((nx - over.nx), (ny - over.ny));

            if (fabs(module) - MIN_NUM_FOR_DIVIDE < 0)
                {
                module = ((rand()%10) + 10)/7;
                vec_ = vec (rand());
                }

            module = 1/module;
            vec_*= module;

            return vec_;
            }

        /*vec normolise (vec speed)
            {
            double module = speed.x*ny - speed.y*nx;
            vec vec_ (ny, -nx);
            vec_*= module;

            return vec_;
            }*/

        nvec operator+ (vec vec_)
            {
            return nvec ((nx + vec_.x)/hypot(nx + vec_.x, ny + vec_.y), (ny + vec_.y)/hypot(nx + vec_.x, ny + vec_.y));
            }

        void operator= (nvec vec_)
            {
            nx = vec_.nx;
            ny = vec_.ny;
            }

        const double getX () const
            {
            return nx;
            }

        const double getY () const
            {
            return ny;
            }
    };

#endif // __NVECTOR_H_INCLUDED__ }
