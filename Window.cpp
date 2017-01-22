#include "Window.hpp"

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM)
{
	INT_PTR result = 0;
	switch(msg)
	{
	case WM_INITDIALOG: 
		{
			HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APPICON));
			SendMessageA(hWnd, WM_SETICON, NULL, reinterpret_cast<LPARAM>(hIcon));

#ifndef NDEBUG
		 	InitConsole(ConsoleMode::CM_OUT);
#endif // NDEBUG
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			std::cout << "f";
			using namespace graphics;
			Rectangle(hDC, 0, 0, 90, 90);
			//HDC loading = reinterpret_cast<HDC>(LoadImageA(GetModuleHandle(nullptr), "Loading.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR));
			//BitBlt(hDC, 0, 0,800, 600, loading, 0, 0, SRCCOPY);
			Graphics::initGL(hDC);
			//DeleteObject(loading);
			Graphics::display();

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_COMMAND: 
		switch(wParam)
		{
		default: break;
		}
		break; 
	case WM_CLOSE: 
		EndDialog(hWnd, NULL); 
		break;
	
	default: break;
	}
	return result;
}

INT StartDialog(HINSTANCE hInstance)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), nullptr, DlgProc, NULL);
	return 0;
}

HWND InitConsole(ConsoleMode mode)
{
	if(::AllocConsole()) 
	{
		INT hCrt = _open_osfhandle(reinterpret_cast<INT_PTR>(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
		if(!hCrt) return FALSE;
  
		if(mode == ConsoleMode::CM_ALL    || mode == ConsoleMode::CM_OUT ||
			mode == ConsoleMode::CM_IN_OUT || mode == ConsoleMode::CM_OUT_ERROR)
		{
			*stdout = *::_fdopen(hCrt, "w");
			::setvbuf(stdout, NULL, _IONBF, 0);
		}

		if(mode == ConsoleMode::CM_ALL      || mode == ConsoleMode::CM_ERROR ||
			mode == ConsoleMode::CM_IN_ERROR || mode == ConsoleMode::CM_OUT_ERROR)
		{
			*stderr = *::_fdopen(hCrt, "w");
			::setvbuf(stderr, NULL, _IONBF, 0);
		}

		if(mode == ConsoleMode::CM_ALL    || mode == ConsoleMode::CM_IN ||
			mode == ConsoleMode::CM_IN_OUT || mode == ConsoleMode::CM_IN_ERROR)
		{
			*stdin = *::_fdopen(hCrt, "r");
			::setvbuf(stdin, NULL, _IONBF, 0);
		}
		std::ios::sync_with_stdio();
	}
	else return FALSE;
	
	HWND console = ::GetConsoleWindow();
	::SetWindowPos(console, NULL, 0, 0, 700, 500, SWP_NOSIZE | SWP_NOZORDER);

	return console;
}