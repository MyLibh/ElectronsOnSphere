#ifndef __PHYSICS_DINAMIC_HPP_INCLUDED__ //{
#define __PHYSICS_DINAMIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"

CONST SIZE_T NUM_ELL = 5;

namespace PHYSICS
    {
    vec Strength (nvec, nvec);

    class PhysicsDynamic
        {
        private:
            std::vector<nvec> _Positions;

            vec PDgetSpeed (size_t num, double speed_coefficient) const;

        protected:
            void PDdoPhysicsDynamic (double speed_coefficient);
            void PDset (std::vector<nvec> positions);
            void PDsetRandom (size_t num);
            const std::vector<nvec>& PDgetVector() const;

            PhysicsDynamic ()
                {PDsetRandom(11);}

            ~PhysicsDynamic ()
                {}
        };
    }

#endif // __PHYSICS_DINAMIC_HPP_INCLUDED__ }
