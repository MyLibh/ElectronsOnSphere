#include "PhysicsDynamic.hpp"

vec Strength(nvec v_to, nvec v_from)
    {
    double module = sqrt (sqr(v_to._X - v_from._X) + sqr(v_to._Y - v_from._Y) + sqr(v_to._Z - v_from._Z))*
                         (sqr(v_to._X - v_from._X) + sqr(v_to._Y - v_from._Y) + sqr(v_to._Z - v_from._Z)); //distanse^3

    vec vec_ ((v_to._X - v_from._X), (v_to._Y - v_from._Y), (v_to._Z - v_from._Z));

    if (fabs(module) - MIN_NUM_FOR_DIVIDE < 0)
        {
        module = 1;
        double alf = rand();
        double btt = rand();
        vec_ = vec (cos(alf), sin(alf)*cos(btt), sin(alf)*sin(btt));
        vec_*=10;
        }

    module = 1/module;
    vec_*= module;

    return vec_;
    }

namespace NPhysics
    {
    namespace NPhysicsDynamic
        {
        std::vector<nvec> physics_dynamic::PDgetVector() const
            {
            return _Positions;
            }

        void physics_dynamic::PDdoPhysicsDynamic ()
            {
            for (size_t i = 0; i < _Positions.size(); i++)
                {
                _Positions[i] = _Positions[i] + PDgetSpeed(i);
                }
            }

        vec physics_dynamic::PDgetSpeed (size_t num) const
            {
            vec sum;
            for (size_t j = 0; j < _Positions.size(); j++)
                {
                if (j != num) sum+= Strength (_Positions[num], _Positions[j]);
                }

            sum*= 0.001;
            return sum;
            }

        void physics_dynamic::PDsetRandom (size_t num)
            {
            std::vector<nvec> tmp(num);
            _Positions.swap(tmp);

            for(size_t i = 0; i < num; ++i)
                {
                Sleep(0);
                double x = rand()%20000 - 10000;
                Sleep(0);
                double y = rand()%20000 - 10000;
                Sleep(0);
                double z = rand()%20000 - 10000;
                double length = sqrt (sqr(x) + sqr(y) + sqr(z));
                _Positions[i] = nvec (x/length, y/length, z/length);

                Sleep (0);
                }
            }

        void physics_dynamic::PDset (std::vector<nvec> positions)
            {
            _Positions.swap(positions);
            }
        }
    }

