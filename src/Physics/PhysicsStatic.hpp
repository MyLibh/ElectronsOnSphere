#ifndef __PHYSICS_STATIC_HPP_INCLUDED__ //{
#define __PHYSICS_STATIC_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.h"
#include "Energy.h"
#include "Saving.h"
#include "PMessage.h"

namespace NPhysics
    {
    namespace NPhysicsStatic
        {
        class physics_static
            {
            private:
                std::string _Name;

                Energy   PSgetPotentialEnergy    (const nvec* positions, size_t ElectronsNum) const;
                PMESSAGE PSsaveWithComaringAsMin (const nvec* positions, size_t ElectronsNum) const;
                PMESSAGE PSsaveAsMin             (const nvec* positions, size_t ElectronsNum) const;
                PMESSAGE PScomareWithMin         (const nvec* positions, size_t ElectronsNum) const;
                PMESSAGE PSsaveAs                (const nvec* positions, size_t ElectronsNum, const char* text);

            protected:
                void     PSdoPhysicsStatic (const nvec* positions, size_t ElectronsNum, PMESSAGE param);

            public:
                physics_static ()
                    {
                    _Name = "Untitled";
                    }
            };
        }
    }

#endif // __PHYSICS_STATIC_HPP_INCLUDED__ }
