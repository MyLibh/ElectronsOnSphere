#ifndef __PHYSICS_DINAMIC_HPP_INCLUDED__ //{
#define __PHYSICS_DINAMIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"

namespace PHYSICS
    {
    vec Strength (nvec, nvec);

    typedef std::vector<nvec> nvector;
    typedef const nvector& crnvector;

    class PhysicsDynamic
        {
        private:
            nvector _Positions;

            vec getSpeed (size_t num, double speed_coefficient) const;

        protected:
            void PDdoPhysicsDynamic (double speed_coefficient);
            void PDset (std::vector<nvec> positions);
            void PDsetRandom (size_t num);
            crnvector PDgetVector() const;

            PhysicsDynamic () { PDsetRandom(11); }
            ~PhysicsDynamic () { }
        };
    }

#endif // __PHYSICS_DINAMIC_HPP_INCLUDED__ }
