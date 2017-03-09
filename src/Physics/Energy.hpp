#ifndef __ENERGY_H_INCLUDED__ // {
#define __ENERGY_H_INCLUDED__

#include "..\Includes.hpp"

class Energy final
{
private:
    int _Number;
    double _Energy;

public:
    Energy (int number) :
        _Number (number),
        _Energy (0)
    { }

    Energy &operator+=(double strenght) 
	{
		_Energy += strenght;
	
		return *this;
	}

    void Out() const { std::cout << "\n\n---------------------\n\nEnergy: " << _Energy << "\nNum:" << _Number << "\n"; }

    int    getNumber() const { return _Number; }
    double getEnergy() const { return _Energy; }
};

#endif // __ENERGY_H_INCLUDED__ }
