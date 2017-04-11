#include "PhysicsDynamic.hpp"

namespace PHYSICS
    {
    vec Strength(nvec v_to, nvec v_from)
        {
        double module = sqrt (sqr(v_to.getX() - v_from.getX()) + sqr(v_to.getY() - v_from.getY()) + sqr(v_to.getZ() - v_from.getZ()))*
                             (sqr(v_to.getX() - v_from.getX()) + sqr(v_to.getY() - v_from.getY()) + sqr(v_to.getZ() - v_from.getZ())); //distanse^3

        vec force ((v_to.getX() - v_from.getX()), (v_to.getY() - v_from.getY()), (v_to.getZ() - v_from.getZ()));

        if (fabs(module) - MIN_NUM_FOR_DIVIDE < 0)
            {
            module = 1;
            double alf = rand();
            double bet = rand();
            force = vec (cos(alf), sin(alf)*cos(bet), sin(alf)*sin(bet));
            force = force*10;
            }

        module = 1/module;

        return force*module;
        }

    const nvector& PhysicsDynamic::getPositions() const
        {
        return _Positions;
        }

    void PhysicsDynamic::doPhysicsDynamic (double speed_coefficient)
        {
        for (size_t i = 0; i < _Positions.size(); i++)
            {
            _Positions[i] = _Positions[i] + getSpeed(i, speed_coefficient);
            }
        }

    vec PhysicsDynamic::getSpeed (size_t num, double speed_coefficient) const
        {
        vec sum;
        for (size_t j = 0; j < _Positions.size(); j++)
            {    
            if (j != num) sum+= Strength (_Positions[num], _Positions[j]);
            }

        return sum*speed_coefficient;
        }

    void PhysicsDynamic::setPositionsRandom (size_t num)
        {
        nvector tmp(num);
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
            }
        }

    void PhysicsDynamic::setPositions (std::auto_ptr<nvector> positions)
        {
        _Positions.swap(*positions.release());
        }
    }

