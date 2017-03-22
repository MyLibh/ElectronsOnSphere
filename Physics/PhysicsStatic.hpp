#ifndef __PHYSICS_STATIC_HPP_INCLUDED__ //{
#define __PHYSICS_STATIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"

namespace NPhysics
    {
    namespace NPhysicsStatic
        {
        class physics_static
            {
            protected:

                double PSgetPotentialEnergy (std::vector<nvec> positions) const;
            };
        }
    }

#endif // __PHYSICS_STATIC_HPP_INCLUDED__ }
