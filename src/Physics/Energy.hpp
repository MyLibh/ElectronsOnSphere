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
            {}

        void operator+= (double strenght)
            {
            _Energy+= strenght;
            }

        void Out()
            {
            std::cout << "\n\n---------------------\n\nEnergy: " << _Energy << "\nNum:" << _Number << "\n";
            }

        int getNumber()
            {
            return _Number;
            }

        double getEnergy()
            {
            return _Energy;
            }
    };

#endif // __ENERGY_H_INCLUDED__ }
