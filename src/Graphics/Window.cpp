#include "Window.hpp"

using namespace graphics;

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM)
{
	INT_PTR result = 0;
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APPICON));
			SendMessage(hWnd, WM_SETICON, NULL, reinterpret_cast<LPARAM>(hIcon));
			SetFocus(hWnd);

			HDC hDC = GetDC(hWnd);
			//HBITMAP hbmLoading = reinterpret_cast<HBITMAP>(LoadImageA(GetModuleHandle(nullptr), "Loading.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			//HDC loading = CreateCompatibleDC(hbmLoading);
			//BitBlt(hDC, 0, 0,800, 600, loading, 0, 0, SRCCOPY);
			graphics::Graphics::setWindowPixelFormatDescriptor(hDC);
			//DeleteObject(hbmLoading);
			//DeleteObject(loading);
			ReleaseDC(hWnd, hDC);

#ifndef NDEBUG
		 	InitConsole(ConsoleMode::CM_OUT);
#endif // NDEBUG
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			graphics::Graphics::initGL(hDC);
			//graphics::Graphics::resize(601, 300);
			graphics::Graphics::display();

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_SAVE:
			break;
		case IDM_LOAD:
			break;
		case IDM_EXIT:
			EndDialog(hWnd, NULL);
			break;

		default: break;
		}
		break;
	case WM_NOTIFY:
		switch(HIWORD(wParam))
		{
		case IDC_COEFSLIDER:
			//std::cout << SendMessage(hWnd, TBM_GETPOS, NULL, NULL);
			break;

		default : break;
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
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), nullptr, DlgProc, 0);
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
			::setvbuf(stdout, nullptr, _IONBF, 0);
		}

		if(mode == ConsoleMode::CM_ALL      || mode == ConsoleMode::CM_ERROR ||
			mode == ConsoleMode::CM_IN_ERROR || mode == ConsoleMode::CM_OUT_ERROR)
		{
			*stderr = *::_fdopen(hCrt, "w");
			::setvbuf(stderr, nullptr, _IONBF, 0);
		}

		if(mode == ConsoleMode::CM_ALL    || mode == ConsoleMode::CM_IN ||
			mode == ConsoleMode::CM_IN_OUT || mode == ConsoleMode::CM_IN_ERROR)
		{
			*stdin = *::_fdopen(hCrt, "r");
			::setvbuf(stdin, nullptr, _IONBF, 0);
		}
		std::ios::sync_with_stdio();
	}
	else return FALSE;

	//HWND console = ::GetConsoleWindow();
	//::SetWindowPos(console, NULL, 0, 0, 700, 500, SWP_NOSIZE | SWP_NOZORDER);

	return nullptr;
}
