#ifndef __PHYSICS_HPP_INCLUDED__ //{
#define __PHYSICS_HPP_INCLUDED__

#include "..\Includes.hpp"

#include "NVector.hpp"
#include "PMessage.h"

namespace physics
{
    class Physics final : public NoncopyableFull
    {
    private:
        std::vector<nvec> _Positions;

        vec getSpeed(size_t);

		VOID assignLocations(size_t);

    public:
        Physics();

		size_t                   getNumberElectrons() const { return _Positions.size(); }
		CONST std::vector<nvec> &getPositions() const { return _Positions; }
		

		PMESSAGE doPhysics();
		VOID     load(CONST std::vector<nvec> &newPos) { _Positions = newPos; }	
    };
	
	Energy GetPotentialEnergy(CONST std::vector<nvec>&);
}

#endif // __PHYSICS_HPP_INCLUDED__ }
