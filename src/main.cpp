#include "App.hpp"

INT APIENTRY WinMain(_In_     HINSTANCE hInstance,
                     _In_opt_ HINSTANCE,
                     _In_     LPTSTR,
                     _In_     INT)
{
#ifdef DEBUG
	InitConsole();
#endif // DEBUG
	
	system("cls");
	srand(static_cast<unsigned int>(time(0)));
	
	App app(hInstance);
	if(!app.init()) return -MessageBox(nullptr, "Failed to start the program", "ERROR", MB_OK | MB_ICONERROR);

	INT result = app.run();

	system("PAUSE");
	return result;
}




