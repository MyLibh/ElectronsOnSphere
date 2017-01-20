#include "stdafx.h"
#include "BaseWindow.hpp"

namespace WinApiWrapper
{
	BaseWindow::BaseWindow(LPCTSTR className, DWORD style, DWORD exstyle, LPCTSTR title, BaseWindow *pParent, HMENU hMenu, HINSTANCE hInstance, CONST WindowRect &rRect, LPVOID pData) :
		wasClassGiven_(FALSE)

	{
		HWND hParent = (pParent == nullptr) ? nullptr : pParent->hWnd_;

		style |= SW_SHOW;

		//if(className == CREATE_CLASS) 
		//if(!registerClass(className, hInstance)) throw "Ќе удалось создать класс окна";
		//else wasClassGiven_ = TRUE

		hWnd_ = ::CreateWindowEx(exstyle, className, title, style, rRect.x, rRect.y, rRect.cx, rRect.cy, hParent, hMenu, hInstance, pData);
		if (hWnd_ == nullptr) throw "ќкно не создано";

		hInst_     = hInstance;
		className_ = className;
		pParent_   = pParent;

		bind(hWnd_);
	}

	BaseWindow::~BaseWindow() 
	{
		if (::IsWindow(hWnd_))
		{
			::MessageBox(nullptr, "Ёкземпл€р уничтожаетс€, но окно существует", "¬нимание", MB_OK | MB_ICONINFORMATION);
			throw "Ёкземпл€р уничтожаетс€, но окно существует";
		}
		if(!wasClassGiven_) ::UnregisterClass(className_.c_str(), hInst_);
		ntfyActionIndexArray_.clear();
	}

	LRESULT BaseWindow::onMessageDefault(UINT msg, WPARAM wParam, LPARAM lParam) { return ::DefWindowProc(hWnd_, msg, wParam, lParam); };

	LRESULT BaseWindow::onMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;
		switch (msg)
		{
		case WM_CREATE:  result = onCreate(msg, wParam, lParam);         break;
		case WM_PAINT:   result = onPaint(msg, wParam, lParam);          break;
		case WM_SIZE:    result = onResize(msg, wParam, lParam);         break;
		case WM_DESTROY: result = onDestroy(msg, wParam, lParam);        break;
		case WM_COMMAND: result = onCommand(msg, wParam, lParam);        break;

		default:         result = onMessageDefault(msg, wParam, lParam); break;
		}

		return result;
	}

	LRESULT BaseWindow::onPaint(UINT msg, WPARAM wParam, LPARAM lParam) { return onMessageDefault(msg, wParam, lParam); }

	LRESULT BaseWindow::onDestroy(UINT, WPARAM, LPARAM) { ::PostQuitMessage(0); return 0; }

	LRESULT BaseWindow::onCommand(UINT msg, WPARAM wParam, LPARAM lParam) { return onMessageDefault(msg, wParam, lParam); }
	
	LRESULT BaseWindow::onCreate(UINT msg, WPARAM wParam, LPARAM lParam) { return onMessageDefault(msg, wParam, lParam); }

	LRESULT BaseWindow::onResize(UINT msg, WPARAM wParam, LPARAM lParam) { return onMessageDefault(msg, wParam, lParam); }

	LRESULT BaseWindow::executeAction(INT, UINT msg, WPARAM wParam, LPARAM lParam) { return onMessageDefault(msg, wParam, lParam); }

	INT BaseWindow::getActionIndex(WORD ntfy)
	{
		for (NotifyBindWithActionIndex &s : ntfyActionIndexArray_)
			if (s.NotifyCode == ntfy) return s.ActionIndex;	

		return -1;
	}

	VOID BaseWindow::setActionIndex(WORD ntfy, INT index)
	{
		for (NotifyBindWithActionIndex &s : ntfyActionIndexArray_)
			if (s.NotifyCode == ntfy)	
			{
				s.ActionIndex = index;

				break;
			}

		ntfyActionIndexArray_.push_back(NotifyBindWithActionIndex(ntfy, index));

	}

	VOID BaseWindow::dump() const
	{
		std::cout << "///////////////////////////////////////////////////////////////\n" <<
			         "hWnd: " << hWnd_ << "hInstance: " << hInst_ << "\n\n";
	}

	LRESULT CALLBACK BaseWindow::baseWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		BaseWindow *pWindow = BaseWindow::getObjectPtr(hWnd);

		return (pWindow)? pWindow->onMessage(msg, wParam, lParam) : DefWindowProc(hWnd, msg, wParam, lParam);
	}

	/*ATOM BaseWindow::registerClass(LPCTSTR className, HINSTANCE hInstance)
	{	
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= baseWndProc;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= ::LoadIcon(wcex.hInstance, NULL);
		wcex.hCursor		= ::LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wcex.lpszClassName	= className;
		wcex.hIconSm		= ::LoadIcon(wcex.hInstance, NULL);

		return RegisterClassEx(&wcex);
	}
	*/

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

} /* namespace WinApiWrapper */