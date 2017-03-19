// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
	srand(static_cast<UINT>(time(nullptr)));

	App app(hInstance);
	if(!app.init()) return -MessageBoxEx(nullptr, "Failed to start the program", "ERROR", MB_OK | MB_ICONERROR, IDOK);

	INT result = app.run();

	system("PAUSE");
	return result;
}




