#pragma once

#ifndef __WINDOW_HPP_INCLUDED__
#define __WINDOW_HPP_INCLUDED__

#include "Includes.hpp"
#include "WinApiWrapper\BaseWindow.hpp"
#include "Graphics.hpp"

using WinApiWrapper::BaseWindow;
using WinApiWrapper::WindowRect;

class Window final : public BaseWindow, private NoncopyableFull
{
private:
	WindowRect window_;

	LRESULT onCreate(UINT, WPARAM, LPARAM) final override;
	LRESULT onResize(UINT, WPARAM, LPARAM) final override;
	LRESULT onDestroy(UINT, WPARAM, LPARAM) final override;
	LRESULT onPaint(UINT msg, WPARAM wParam, LPARAM lParam) final override { graphics::Graphics::display(); return onMessageDefault(msg, wParam, lParam); };

	friend ATOM registerClass(CONST std::string&, HINSTANCE);

public:
	Window(LPCTSTR, DWORD, LPCTSTR, HINSTANCE, CONST WindowRect&);
	~Window() { };

	inline CONST WindowRect __nothrow &getWindowRect() const { return window_; };
};

struct MainLoopParameters
{
	Window      *pWindow;
	std::string  className;

	CONST Window __nothrow &getWindow() const { return *pWindow; };

	MainLoopParameters(HINSTANCE, CONST WindowRect&);
	~MainLoopParameters();
};
	
typedef void MLFUNC;
typedef MLFUNC (*LPMLFUNC)();

INT MainLoop(LPMLFUNC = nullptr, MainLoopParameters* = nullptr);

#endif