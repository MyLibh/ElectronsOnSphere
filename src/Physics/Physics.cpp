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
    { assignLocations(5); }

	VOID Physics::assignLocations(size_t num)
	{
		std::vector<nvec> tmp(num);
		_Positions.swap(tmp);

		for(size_t i = 0; i < num; ++i)
		{
			double alf = rand();
			_Positions[i] = nvec (alf);

			Sleep(0);
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
}

