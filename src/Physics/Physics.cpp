// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Physics.hpp"

#ifdef __PHYSICS_VER__
    #error physics ver defined
#else
    #define __PHYSICS_VER__ 1.1
#endif // __PHYSICS_VER__

namespace physics
{
	Physics::Physics() :
		_Positions()
    { assignLocations(8); }

	VOID Physics::assignLocations(size_t num)
	{
		std::vector<nvec> tmp(num);
		_Positions.swap(tmp);

		for(size_t i = 0; i < num; ++i)
		{
			double alf = rand();
			_Positions[i] = nvec (alf);

			SleepEx(0, FALSE);
		}
	}

    PMESSAGE Physics::doPhysics()
    {
        bool big = false;
        for(size_t i = 0; i < _Positions.size(); ++i)
        {
            if (false) big = true;
            _Positions[i] = _Positions[i] + getSpeed(i);
        }
		return ((big)? PD_R_DOSTATIC : PD_R_EMPTY);
     }

    vec Physics::getSpeed(size_t num)
    {
        vec sum;
        for(size_t i = 0; i < _Positions.size(); ++i)
			if(i != num) sum += _Positions[num].strength(_Positions[i]);

        return sum * 0.001;
    }

	Energy GetPotentialEnergy(CONST std::vector<nvec> &crPositions)
    {
        Energy energy (crPositions.size());
        for(size_t i = 0; i < crPositions.size(); ++i)
            for(size_t j = 0; j < i; ++j)
            {
                double module = ((crPositions[i].getX() - crPositions[j].getX()) * (crPositions[i].getX() - crPositions[j].getX()) +
                                 (crPositions[i].getY() - crPositions[j].getY()) * (crPositions[i].getY() - crPositions[j].getY()));

                if(fabs(module) - MIN_NUM_FOR_DIVIDE < 0)
                {
                    module = MIN_NUM_FOR_DIVIDE;
                    std::cerr << "ERROR";
                }

                module = 1 / module;
                energy += module;
            }

    return energy;
    }
}

