// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Includes.hpp"

#ifdef _MSC_VER
    #pragma comment(lib, "opengl32.lib")
    #pragma comment(lib, "glu32.lib")
#endif // _MSC_VER

#ifdef DEBUG

	VOID DBG(CONST std::string &crInf, DBGMODE mode)
	{
		switch(mode)
		{
		case DBGMODE::INFO:
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>((0 << 4) | 15));
			std::cout << "[INFO]\t";
			break;
		}

		case DBGMODE::FAIL:
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>((0 << 4) | 4));
			std::cout << "[ERROR]\t";
			break;
		}

		case DBGMODE::STATUS:
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>((0 << 4) | 2));
			std::cout << "[STATUS]\t";
			break;
		}

		default: break;
		};

		std::cout << __TIME__ << "\t" << crInf << std::endl;
	}

#endif // DEBUG
