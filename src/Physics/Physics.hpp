#ifndef __PHYSICS_HPP_INCLUDED__ //{
#define __PHYSICS_HPP_INCLUDED__

#include "PhysicsDynamic.hpp"
#include "PhysicsStatic.hpp"

namespace PHYSICS
    {
    class Physics : public PhysicsDynamic, public PhysicsStatic
        {
        private:
            double _SpeedCoefficient;

        public:
            Physics () :
                _SpeedCoefficient (0.001)
                {}

            void doPhysics ();
            void setSpeedCoefficient (double value);

			double getPotentialEnergy () const { return PhysicsStatic::getPotentialEnergy (getPositions ()); }
        };
    }

#endif // __PHYSICS_HPP_INCLUDED__ }

