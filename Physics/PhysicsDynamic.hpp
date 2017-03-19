#ifndef __PHYSICS_DINAMIC_HPP_INCLUDED__ //{
#define __PHYSICS_DINAMIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"

CONST SIZE_T NUM_ELL = 5;

namespace NPhysics
    {
    namespace NPhysicsDynamic
        {
        class physics_dynamic
            {
            private:
                std::vector<nvec> _Positions;

                vec PDgetSpeed (size_t num) const;

            protected:
                void PDdoPhysicsDynamic ();
                void PDset (std::vector<nvec> positions);
                void PDsetRandom (size_t num);
                std::vector<nvec> PDgetVector() const;

                physics_dynamic ()
                    {PDsetRandom(11);}

                ~physics_dynamic ()
                    {}
            };
        }
    }

#endif // __PHYSICS_DINAMIC_HPP_INCLUDED__ }
