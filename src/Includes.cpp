#include "Includes.hpp"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#ifdef DEBUG

	VOID DBG(std::string inf, DBGMODE mode)
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

		std::cout << __TIME__ << "\t" << inf << std::endl;
	}

#endif // DEBUG