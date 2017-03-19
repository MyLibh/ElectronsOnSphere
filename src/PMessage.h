#include "Energy.h"

#ifndef __PMESSAGE_H_INCLUDED__
#define __PMESSAGE_H_INCLUDED__

#define PD_R_EMPTY         100
#define PD_R_DOSTATIC      101

#define PS_S_MINTRUE       110
#define PS_S_MINFALSE      111

#define VK_P_CONTROLS      120
#define VK_P_CONTROLSHIFTS 121
#define VK_P_CONTROLO      122


class PMESSAGE
    {
    private:
        int Msg;

    public:
        PMESSAGE (int value) :
            Msg (value)
            {}

        bool operator== (int value)
            {
            return Msg == value;
            }

        int Get ()
            {
            return Msg;
            }
    };

/*void PReadFile (ifstream fp, PMESSAGE format, void* Plase)
    {
    switch (format.Get())
        {
        case PS_F_GETENERGY:
            {
            double energy = 0;

            Energy* en = (Energy*) Plase;

            if (!fp.is_open()) cout << "laga.big";

            fp.seekg (0);

            char text[50];

            fp >> text;
            fp >> text;
            fp >> text;
            fp >> text;
            fp >> energy;

            *en = (Energy (energy));

            break;
            }

        default:
            {
            cout << "unindefined comand";
            break;
            }
        }
    }
*/

#endif // __PMESSAGE_H_INCLUDED__
