#ifndef __PHYSICS_HPP_INCLUDED__ //{
#define __PHYSICS_HPP_INCLUDED__

#include "PhysicsDynamic.hpp"
#include "PhysicsStatic.hpp"

namespace NPhysics
    {
    vec Strangth(nvec v_to, nvec v_from);

    class physics : protected NPhysicsDynamic::physics_dynamic, protected NPhysicsStatic::physics_static
        {
        public:
            physics ()
                {}

            void doPhysics ();
            double getPotentialEnergy ();
            std::vector<nvec> getVector ();
            void setVector (std::vector<nvec> positions);
            void setVectorRandom (size_t num);
        };
    }

#endif // __PHYSICS_HPP_INCLUDED__ }

