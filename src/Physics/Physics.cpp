#include "Physics.hpp"

#ifdef __PHYSICS_VER__ //{

    #error physics ver defined

#else

    #define __PHYSICS_VER__ 1.1

#endif                 //}


namespace NPhysics
    {
    inline void  physics::doPysics()
        {
        PDdoPhysicsDynamic ();

        if (GetAsyncKeyState (VK_CONTROL) && GetAsyncKeyState ('S'))
            PSdoPhysicsStatic (PDgetPositions(), PDgetNumberElectrons(), (GetAsyncKeyState(VK_SHIFT))? VK_P_CONTROLS : VK_P_CONTROLSHIFTS);

        while (GetAsyncKeyState (VK_CONTROL) && GetAsyncKeyState ('S')) {}
        }

    inline nvec* physics::getPositions()
        {
        return PDgetPositions();
        }
    }



