#ifndef __PHYSICS_DINAMIC_HPP_INCLUDED__ //{
#define __PHYSICS_DINAMIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"


namespace PHYSICS
    {
    vec Strength (nvec, nvec);

    class PhysicsDynamic
        {
        private:
            nvector _Positions;

            vec getSpeed (size_t num, double speed_coefficient) const;

        protected:
            void doPhysicsDynamic (double speed_coefficient);

        public:
            void setPositions (std::auto_ptr<nvector> positions);
            void setPositionsRandom (size_t num);
            const nvector& getPositions() const;

            PhysicsDynamic () { setPositionsRandom(11); }
            ~PhysicsDynamic () { }
        };
    }

#endif // __PHYSICS_DINAMIC_HPP_INCLUDED__ }
