#include "PhysicsStatic.hpp"

namespace PHYSICS
    {
    double PhysicsStatic::getPotentialEnergy (nvector positions) const
        {
        double energy = 0;
        for (size_t i = 0; i < positions.size(); i++)
            for (size_t j = 0; j < i; j++)
                {
                double module = ((positions[i].getX() - positions[j].getX())*(positions[i].getX() - positions[j].getX()) +
                                 (positions[i].getY() - positions[j].getY())*(positions[i].getY() - positions[j].getY()));
                if (fabs(module) - MIN_NUM_FOR_DIVIDE < 0)
                    {
                    module = MIN_NUM_FOR_DIVIDE;
                    DBG("Minimal energy equal infinity", DBGMODE::FAIL);
                    }

                module = 1/module;
                energy+= module;
                }
        return energy;
        }
    }

                            