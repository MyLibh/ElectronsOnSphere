#include "Window.hpp"

Window::Window(LPCTSTR className, DWORD style, LPCTSTR title, HINSTANCE hInstance, CONST WindowRect &crRect) :
	BaseWindow(className, style, NULL, title, nullptr, nullptr, hInstance, crRect), 
	window_(crRect)
{ }

LRESULT Window::onCreate(UINT msg, WPARAM wParam, LPARAM lParam) 
{ 
	HDC hDC = GetDC(hWnd_);

	graphics::Graphics::initGL(hDC);

	ReleaseDC(hWnd_, hDC);
	return onMessageDefault(msg, wParam, lParam);
}

inline LRESULT Window::onResize(UINT msg, WPARAM wParam, LPARAM lParam) { graphics::Graphics::resize(LOWORD(lParam), HIWORD(wParam)); return onMessageDefault(msg, wParam, lParam); }

inline LRESULT Window::onDestroy(UINT msg, WPARAM wParam, LPARAM lParam) { graphics::Graphics::deleteGL(); return onMessageDefault(msg, wParam, lParam); }

ATOM registerClass(CONST std::string &rClassName, HINSTANCE hInst)
{
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };

	wcex.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= Window::baseWndProc;
	wcex.hInstance		= hInst;
	wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszClassName	= rClassName.c_str();
	wcex.hIconSm		= LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));

	return RegisterClassEx(&wcex);
}

MainLoopParameters::MainLoopParameters(HINSTANCE hInstance, CONST WindowRect &crRect) :
	pWindow(nullptr),
	className("ElectronsOnSphere")
{
	registerClass(className, hInstance);
		
	pWindow = new Window(className.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, className.c_str(), hInstance, crRect);
	pWindow->show();
}

MainLoopParameters::~MainLoopParameters() { delete(pWindow); }

INT MainLoop(LPMLFUNC func, MainLoopParameters *pParams)
{
	MSG  msg  = { };
	HWND hWnd = pParams->pWindow->getHWND();

	//ShowWindow(hWnd, pParams->nCmdShow);
	//pParams->pWindow->update();

#pragma warning(push)
#pragma warning(disable:4127) // Избежание warning'a в строке "while (TRUE)"
	while(TRUE && !GetAsyncKeyState(VK_ESCAPE))
	{
		while(PeekMessage(&msg, hWnd, 0, 0, PM_NOREMOVE))
			if(GetMessage(&msg, hWnd, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else return static_cast<INT>(msg.wParam);
		 
		func();
	}
#pragma warning(pop)

	return static_cast<INT>(msg.wParam);
}