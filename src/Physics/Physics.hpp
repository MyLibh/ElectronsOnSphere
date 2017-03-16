#ifndef __PHYSICS_HPP_INCLUDED__ 
#define __PHYSICS_HPP_INCLUDED__

#include "..\Includes.hpp"
#include "NVector.hpp"
#include "Energy.hpp"

namespace physics
{
	Energy GetPotentialEnergy(CONST std::vector<nvec>&);

    class Physics final : public NoncopyableFull
    {
    private:
        std::vector<nvec> _Positions;

        vec getSpeed(size_t);

    public:
        Physics();

		size_t                   getNumberElectrons() const { return _Positions.size(); }
		CONST std::vector<nvec> &getPositions()       const { return _Positions; }
		

		VOID doPhysics();
		VOID load(CONST std::vector<nvec> &crPos) { _Positions = crPos; }	
		VOID assignLocations(size_t);
    };
	
	
}

#endif // __PHYSICS_HPP_INCLUDED__ 
