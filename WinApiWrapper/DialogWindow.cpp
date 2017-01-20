#include "stdafx.h"
#include "DialogWindow.hpp"

namespace WinApiWrapper
{
	INT DialogWindow::dlgCount_ = 0;

	DialogWindow::DialogWindow(DialogWindowStyle style, DWORD exstyle, LPCTSTR title, BaseWindow *pParent, HMENU hMenu, HINSTANCE hInst, CONST WindowRect &rRect) : 
		BaseWindow(getDlgWndClsName(hInst), style, exstyle, title, pParent, hMenu, hInst, rRect)
	{}

	DialogWindow::~DialogWindow()
	{
		dlgCount_--;

		//if (dlgCount_ == 0) ::UnregisterClass(className_.c_str(), hInst_);
	}

	LPCTSTR DialogWindow::getDlgWndClsName(HINSTANCE hInst)
	{
		static LPCTSTR className = "DlgWndCls";
		if (dlgCount_ == 0)
		{
			WNDCLASSEX wcex    = { sizeof(WNDCLASSEX) };
			wcex.style         = CS_HREDRAW|CS_VREDRAW;
			wcex.hInstance     = hInst;
			wcex.lpfnWndProc   = &BaseWindow::baseWndProc;
			wcex.lpszClassName = className;
			wcex.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
			wcex.hIcon         = ::LoadIcon(NULL, IDI_APPLICATION);
			wcex.hIconSm       = ::LoadIcon(NULL, IDI_APPLICATION);
			wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

			if(!RegisterClassEx(&wcex)) MessageBox(nullptr, "d", "f", MB_OK);
			//if(!registerClass(CREATE_CLASS, hInst)) throw "Не удалось создать класс окна\n";
		}
		dlgCount_++;	

		return className;
	}

	LRESULT DialogWindow::onCommand(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = onMessageDefault(msg, wParam, lParam);

		if (lParam != 0)	
		{
			BaseWindow *pCtrl = BaseWindow::getObjectPtr(reinterpret_cast<HWND>(lParam));	

			if (pCtrl)
			{

				INT index = pCtrl->getActionIndex(HIWORD(wParam));		

				result = executeAction(index, msg, wParam, lParam);
			}
		}

		return result;
	}
};