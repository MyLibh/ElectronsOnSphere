#include "Physics.hpp"

#ifdef __PHYSICS_VER__ //{

    #error physics ver defined

#else

    #define __PHYSICS_VER__ 2.3

#endif                 //}


namespace PHYSICS
    {
    void Physics::doPhysics()
        {
        doPhysicsDynamic (_SpeedCoefficient);
        }

   double Physics::getPotentialEnergy ()
        {
        return getPotentialEnergyByPositions (getPositions ());
        }

    void Physics::setSpeedCoefficient (double value)
        {
        _SpeedCoefficient = value;
        }
    }



