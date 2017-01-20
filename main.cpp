#include "Includes.hpp"
#include "Graphics.hpp"
#include "Window.hpp"

MLFUNC Display();

using namespace graphics;
using namespace WinApiWrapper;

INT APIENTRY WinMain(_In_     HINSTANCE hInstance,
                     _In_opt_ HINSTANCE,
                     _In_     LPTSTR,
                     _In_     INT)
{
	WinApiWrapper::InitConsole();

	WindowRect window = { 0, 0, 800, 600 };
	MainLoopParameters mlp(hInstance, window);

	//Graphics::initGL(GetDC(mlp.pWindow->getHWND()));
	INT result = MainLoop(Display, &mlp);
	Graphics::deleteGL();

	return result;
}

MLFUNC Display()
{
	Graphics::display();
	Graphics::manage();
	//Sleep(200);
}


