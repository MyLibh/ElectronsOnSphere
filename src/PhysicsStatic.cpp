#include "PhysicsStatic.hpp"

namespace NPhysics
    {
    namespace NPhysicsStatic
        {
        PMESSAGE physics_static::PSsaveAs                (const nvec* positions, size_t ElectronsNum, const char* text_)
            {
            char text[200] = "";

            //string text_ = "Saving_Information\\configuration_for_2D_of_";
            //text_+= ElectronsNum;
            //text_+= "_electrons_min_energy.txt";

            //cout << "\n\n" << text_;

            sprintf (text, "Saving_Information\\configuration_for_2D_of_%d_electrons_%s.txt", ElectronsNum, text_);

            std::ofstream fp (text);

            if(!fp.is_open())
                {
                fp.close();
                std::cerr << "\n__cannot open file__:" << text << "\n\n";
                return PMESSAGE (PS_S_MINFALSE);
                }
            else
                {
                fp << "colvo electrons: " << ElectronsNum << ",\nenergy: " << PSgetPotentialEnergy (positions, ElectronsNum).getEnergy() << "\n\npositions:";

                for (size_t i = 0; i < ElectronsNum; i++)
                    {
                    fp << "\n\npoint№" << i + 1 << "\n";

                    fp << "x: "   << positions[i].getX() << ",\n";
                    fp << "y: "   << positions[i].getY() << ",\n";
                    fp << "alf: " << atan_(positions[i].getX(), positions[i].getY()) << ".";
                    }
                }

            fp.close();

            return PS_S_MINTRUE;
            }

        PMESSAGE physics_static::PSsaveAsMin             (const nvec* positions, size_t ElectronsNum) const
            {
            Energy en = PSgetPotentialEnergy (positions, ElectronsNum);
            en.Out();

            char text[100] = "";

            //string text_ = "Saving_Information\\configuration_for_2D_of_";
            //text_+= ElectronsNum;
            //text_+= "_electrons_min_energy.txt";

            //cout << "\n\n" << text_;

            sprintf (text, "Saving_Information\\configuration_for_2D_of_%d_electrons_min_energy.txt", ElectronsNum);

            std::ofstream fp (text);

            if(!fp.is_open())
                {
                std::cerr << "\n__cannot open file__:" << text << "\n\n";
                return PMESSAGE (PS_S_MINFALSE);
                }
            else
                {
                fp << "colvo electrons: " << ElectronsNum << ",\nenergy: " << en.getEnergy() << "\n\npositions:";

                for (size_t i = 0; i < ElectronsNum; i++)
                    {
                    fp << "\n\npoint¹" << i + 1 << "\n";

                    fp << "x: "   << positions[i].getX() << ",\n";
                    fp << "y: "   << positions[i].getY() << ",\n";
                    fp << "alf: " << atan_(positions[i].getX(), positions[i].getY()) << ".";
                    }
                }

            fp.close();

            return PS_S_MINTRUE;
            }

        PMESSAGE physics_static::PScomareWithMin         (const nvec* positions, size_t ElectronsNum) const
            {
            Energy en = PSgetPotentialEnergy (positions, ElectronsNum);
            double energy = 0;

            char text[100] = "";

            //string text_ = "Saving_Information\\configuration_for_2D_of_";
            //text_+= ElectronsNum;
            //text_+= "_electrons_min_energy.txt";

            sprintf (text, "Saving_Information\\configuration_for_2D_of_%d_electrons_min_energy.txt", ElectronsNum);

            std::ifstream fp (text);

            if(!fp.is_open())
                {
                fp.close();

                return PMESSAGE (PS_S_MINTRUE);
                }
            else
                {
                fp >> text >> text >> text >> text;
                fp >> energy;

                if (en.getEnergy() < energy)
                    {
                    fp.close();

                    return PMESSAGE (PS_S_MINTRUE);
                    }
                }

            fp.close();

            return PMESSAGE (PS_S_MINFALSE);
            }

        PMESSAGE physics_static::PSsaveWithComaringAsMin (const nvec* positions, size_t ElectronsNum) const
            {
            if (PScomareWithMin (positions, ElectronsNum) == PS_S_MINTRUE)
                {
                PSsaveAsMin (positions, ElectronsNum);

                return PS_S_MINTRUE;
                }

            return PS_S_MINFALSE;
            }

        void     physics_static::PSdoPhysicsStatic     (const nvec* positions, size_t ElectronsNum, PMESSAGE)
            {
            PSsaveWithComaringAsMin (positions, ElectronsNum);
            //cout << "do you want to save it?";
            //string text;
            //cin >> text;
            //PSsaveAs (positions, ElectronsNum, text);
            }

        Energy   physics_static::PSgetPotentialEnergy  (const nvec* positions, size_t ElectronsNum) const
            {
            Energy energy (ElectronsNum);
            for (size_t i = 0; i < ElectronsNum; i++)
                for (size_t j = 0; j < i; j++)
                    {
                    double module = ((positions[i].getX() - positions[j].getX())*(positions[i].getX() - positions[j].getX()) +
                                     (positions[i].getY() - positions[j].getY())*(positions[i].getY() - positions[j].getY()));
                    if (fabs(module) - MIN_NUM_FOR_DIVIDE < 0)
                        {
                        module = MIN_NUM_FOR_DIVIDE;
                        std::cerr << "ERROR";
                        }

                    module = 1/module;
                    energy+= module;
                    }
            return energy;
            }
        }
    }

