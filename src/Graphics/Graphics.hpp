#pragma once

#include "..\Includes.hpp"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//=====================================================================================================================

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

HWND InitConsole(ConsoleMode = ConsoleMode::CM_ALL);
HWND CreateTrackBar(HWND, UINT, UINT, UINT, UINT);

//=====================================================================================================================

class Graphics : public NoncopyableFull
{
private:
	HWND        hWnd_;
	HINSTANCE   hInstance_;
	HDC         hDC_;
	HGLRC       hRC_;
	UINT        width_,
		        height_;
	std::string title_;
	FLOAT       fps_;
	DWORD       wndStyle_;

	BOOL initWindow();
	BOOL initGL();
	VOID showFPS(FLOAT);
	VOID shutdown();

	friend class App;

public:
	Graphics(HINSTANCE);
	~Graphics() { }

	BOOL init();
	VOID render();
	LRESULT wndProc(HWND, UINT, WPARAM, LPARAM);
};