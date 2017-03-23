#include "Physics.hpp"

#ifdef __PHYSICS_VER__ //{

    #error physics ver defined

#else

    #define __PHYSICS_VER__ 1.9

#endif                 //}


namespace NPhysics
    {
    void physics::doPhysics()
        {
        PDdoPhysicsDynamic ();
        }

    std::vector<nvec> physics::getVector()
        {
        return PDgetVector();
        }

    double physics::getPotentialEnergy ()
        {
        return PSgetPotentialEnergy (PDgetVector ());
        }

    void physics::setVector (std::vector<nvec> positions)
        {
        PDset (positions);
        }

    void physics::setVectorRandom (size_t num)
        {
        PDsetRandom (num);
        }
    }



