#include "Includes.hpp"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#ifdef DEBUG

	VOID DBG(std::string inf, DBGMODE mode)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>((0 << 4) | ((mode == DBGMODE::FAIL)? 4 : 15)));

		std::cout << ((mode == DBGMODE::INFO)? "[INFO]\t" : "[ERROR]\t") << __TIME__ << "\t" << inf << std::endl;
	}

#endif // DEBUG