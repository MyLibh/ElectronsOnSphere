#include "Includes.hpp"
#include "Graphics\Graphics.hpp"

INT APIENTRY WinMain(_In_     HINSTANCE hInstance,
                     _In_opt_ HINSTANCE,
                     _In_     LPTSTR,
                     _In_     INT)
{
	InitConsole();
	Graphics graphics(hInstance);
	if(!graphics.init()) return -1;

	INT result = graphics.run();

	system("PAUSE");
	return result;
}




