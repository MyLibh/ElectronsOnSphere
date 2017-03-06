#include "App.hpp"

INT APIENTRY WinMain(_In_     HINSTANCE hInstance,
                     _In_opt_ HINSTANCE,
                     _In_     LPTSTR,
                     _In_     INT)
{
	InitConsole();
	App app(hInstance);
	if(!app.init()) return -1;

	INT result = app.run();

	system("PAUSE");
	return result;
}




