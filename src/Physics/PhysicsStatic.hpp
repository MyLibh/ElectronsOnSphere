#ifndef __PHYSICS_STATIC_HPP_INCLUDED__ //{
#define __PHYSICS_STATIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"

namespace PHYSICS
    {
    class PhysicsStatic
        {
        protected:

            double PSgetPotentialEnergy (std::vector<nvec> positions) const;
        };
    }

#endif // __PHYSICS_STATIC_HPP_INCLUDED__ }
