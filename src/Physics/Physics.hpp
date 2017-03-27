#ifndef __PHYSICS_HPP_INCLUDED__ //{
#define __PHYSICS_HPP_INCLUDED__

#include "PhysicsDynamic.hpp"
#include "PhysicsStatic.hpp"

namespace PHYSICS
    {
    vec Strength(nvec v_to, nvec v_from);

    class Physics : public PhysicsDynamic, public PhysicsStatic
        {
        private:
            double _SpeedCoefficient;

        public:
            Physics () :
                _SpeedCoefficient (0.001)
                {}

            void doPhysics ();
            //double getPotentialEnergy ();
            //const nvector& getPositions ();
            //void setPositions (nvector positions);
            //void setPositionsRandom (size_t num);
            void setSpeedCoefficient (double value);
        };
    }

#endif // __PHYSICS_HPP_INCLUDED__ }

