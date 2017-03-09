#pragma once

#include "..\Includes.hpp"
#include "..\Physics\NVector.hpp"
#include "..\Control.hpp"

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

//=====================================================================================================================

class Graphics final : public NoncopyableFull
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

	BOOL initWindow(WNDPROC);
	BOOL initGL();
	VOID showFPS(FLOAT);
	VOID shutdown();

	friend class App;

public:
	Graphics(HINSTANCE);
	~Graphics() { }

	BOOL init(WNDPROC);
	VOID render(CONST Control&, CONST std::vector<nvec>&);
};

