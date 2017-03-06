#include "Includes.hpp"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#ifdef DEBUG

	VOID DBG(std::string inf, DBGMODE mode)
	{
		if(mode == DBGMODE::FAIL) system("color 0C");
		else                      system("color 0F");

		std::cout << ((mode == DBGMODE::INFO)? "[INFO]\t" : "[ERROR]\t") << __TIME__ << "\t" << inf << std::endl;
	}

#endif // DEBUG