#pragma once

#ifndef __BASEWINDOW_HPP_INCLUDED__
#define __BASEWINDOW_HPP_INCLUDED__

#include "stdafx.h"

namespace WinApiWrapper
{
	struct WindowRect
	{
		INT x, 
			y;

		SIZE_T cx, 
			   cy;
	};

	struct NotifyBindWithActionIndex
	{
		WORD NotifyCode;	
		INT  ActionIndex;

		NotifyBindWithActionIndex(WORD ntfy, INT index) : NotifyCode(ntfy), ActionIndex(index) {}
	};

	static CONST WCHAR *CREATE_CLASS = L"CreateNew";

	class BaseWindow
	{	
	private:
		BOOL                                   wasClassGiven_;
		std::vector<NotifyBindWithActionIndex> ntfyActionIndexArray_;

		inline VOID bind(HWND hWnd) { ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)); };
		
	protected:
		HINSTANCE     hInst_;
		HWND          hWnd_;
		std::string  className_;
		BaseWindow   *pParent_;

		VOID setActionIndex(WORD, INT);

		VOID dump() const;

		//virtual ATOM registerClass(LPCTSTR, HINSTANCE) = 0;

		static  LRESULT CALLBACK baseWndProc(HWND, UINT, WPARAM, LPARAM);
		virtual LRESULT onMessageDefault(UINT, WPARAM, LPARAM);
		virtual LRESULT onMessage(UINT, WPARAM, LPARAM);
		virtual LRESULT onPaint(UINT, WPARAM, LPARAM);
		virtual LRESULT onDestroy(UINT, WPARAM, LPARAM);
		virtual LRESULT onCommand(UINT, WPARAM, LPARAM);
		virtual LRESULT onCreate(UINT, WPARAM, LPARAM);
		virtual LRESULT onResize(UINT, WPARAM, LPARAM);

		virtual LRESULT executeAction(INT, UINT, WPARAM, LPARAM);

	public:
		BaseWindow(LPCTSTR, DWORD, DWORD, LPCTSTR, BaseWindow*, HMENU, HINSTANCE, CONST WindowRect&, LPVOID = nullptr);
		virtual ~BaseWindow();

		static inline BaseWindow *getObjectPtr(HWND hWnd) { return reinterpret_cast<BaseWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA)); };
		static inline WNDPROC getWndProc(HWND hWnd) { return reinterpret_cast<WNDPROC>(::GetWindowLongPtr(hWnd, GWLP_WNDPROC)); };

		inline HWND        getHWND()         const { return hWnd_; };
		inline HINSTANCE   getHINSTANCE()    const { return hInst_; };
		inline LPCTSTR     getClassName()    const { return className_.c_str(); };
		inline BaseWindow *getParentWindow() const { return pParent_; };

		inline VOID show() 	  { ::ShowWindow(hWnd_, SW_SHOW); };
		inline VOID hide() 	  { ::ShowWindow(hWnd_, SW_HIDE); };
		inline VOID update()  { ::UpdateWindow(hWnd_); };
		inline VOID destroy() { ::DestroyWindow(hWnd_); };

		int getActionIndex(WORD);

		static inline WNDPROC initSubclassing(HWND hWnd, WNDPROC proc) { return reinterpret_cast<WNDPROC>(::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(proc))); };
		static inline WNDPROC doneSubclassing(HWND hWnd, WNDPROC baseProc) { return initSubclassing(hWnd, baseProc); };
	};

	typedef BaseWindow Window;

	enum ConsoleMode 
	{
		CM_ALL = 0,

		CM_OUT, 
		CM_IN,
		CM_ERROR,

		CM_IN_OUT,
		CM_IN_ERROR,
		CM_OUT_ERROR
	};

	HWND InitConsole(ConsoleMode = CM_ALL);
} /* namespace __BASEWINDOW_HPP_INCLUDED__ */

#endif /* __BASEWINDOW_HPP_INCLUDED__ */