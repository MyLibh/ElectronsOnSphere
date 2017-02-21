#ifndef __PHYSICS_DINAMIC_HPP_INCLUDED__ //{
#define __PHYSICS_DINAMIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"
#include "PMessage.h"

CONST SIZE_T NUM_ELL = 5;

namespace NPhysics
    {
    namespace NPhysicsDynamic
        {
        class physics_dynamic
            {
            private:
                size_t   _ElectronsNum;
                nvec*    _Positions;

                vec      PDgetSpeed (size_t num) const;

            protected:
                PMESSAGE PDdoPhysicsDynamic ();
                void     PDset (size_t num, nvec* positions);
         inline nvec*    PDgetPositions() const;
         inline size_t   PDgetNumberElectrons() const;

                physics_dynamic () :
                    _ElectronsNum  (0),
                    _Positions (NULL)
                    {
                    _ElectronsNum = NUM_ELL;
                    _Positions = new nvec [_ElectronsNum];//(nvec*) calloc(ElectronsNum, sizeof(nvec));

                    for (size_t i = 0; i < _ElectronsNum; i++)
                        {
                        double alf = rand();
                        _Positions[i] = nvec (alf);

                        Sleep(0);
                        }
                    }

                ~physics_dynamic ()
                    {
                    delete []_Positions;
                    }
            };
        }
    }

#endif // __PHYSICS_DINAMIC_HPP_INCLUDED__ }
