#ifndef __PHYSICS_HPP_INCLUDED__ //{
#define __PHYSICS_HPP_INCLUDED__

#include "PhysicsDynamic.hpp"
#include "PhysicsStatic.hpp"

namespace NPhysics
    {
    class physics : protected NPhysicsDynamic::physics_dynamic, protected NPhysicsStatic::physics_static
        {
        public:
            physics ()
                {}

            inline void  doPysics ();
            inline nvec* getPositions ();
        };
    }

#endif // __PHYSICS_HPP_INCLUDED__ }

