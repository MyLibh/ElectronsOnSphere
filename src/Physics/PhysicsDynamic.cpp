#include "PhysicsDynamic.hpp"

namespace NPhysics
    {
    namespace NPhysicsDynamic
        {
 inline nvec*    physics_dynamic::PDgetPositions() const
            {
            return _Positions;
            }

 inline size_t   physics_dynamic::PDgetNumberElectrons() const
            {
            return _ElectronsNum;
            }

        PMESSAGE physics_dynamic::PDdoPhysicsDynamic ()
            {
            bool big = false;
            for (size_t i = 0; i < _ElectronsNum; i++)
                {
                if (false) big = true;
                _Positions[i] = _Positions[i] + PDgetSpeed(i);
                }
            if (!big) return PMESSAGE(PD_R_EMPTY);
            else return PMESSAGE(PD_R_DOSTATIC);
            }

        vec      physics_dynamic::PDgetSpeed (size_t num) const
            {
            vec sum;
            for (size_t j = 0; j < _ElectronsNum; j++)
                {
                if (j != num) sum += _Positions[num].strangth (_Positions[j]);
                }

            sum*= 0.001;
            return sum;
            }

        void     physics_dynamic::PDset (size_t num, nvec* positions_)
            {
            std::cout << "\nnot realised\n";
            //ElectronsNum = num;
            //Positions = positions_;
            }
        }
    }

