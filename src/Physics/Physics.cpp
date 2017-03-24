#include "Physics.hpp"

#ifdef __PHYSICS_VER__ //{

    #error physics ver defined

#else

    #define __PHYSICS_VER__ 1.9

#endif                 //}


namespace PHYSICS
    {
    void Physics::doPhysics()
        {
        PDdoPhysicsDynamic (_SpeedCoefficient);
        }

    const std::vector<nvec>& Physics::getPositions()
        {
        return PDgetVector();
        }

    double Physics::getPotentialEnergy ()
        {
        return PSgetPotentialEnergy (PDgetVector ());
        }

    void Physics::setPositions (std::vector<nvec> positions)
        {
        PDset (positions);
        }

    void Physics::setPositionsRandom (size_t num)
        {
        PDsetRandom (num);
        }

    void Physics::setSpeedCoefficient (double value)
        {
        _SpeedCoefficient = value;
        }
    }



