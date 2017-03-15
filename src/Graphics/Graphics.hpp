#pragma once

#include "..\Includes.hpp"
#include "Color.hpp"
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

	Color4f     nucleusColor_,
				electronsColor_,
				sphereColor_;

	BOOL initWindow(WNDPROC);
	BOOL initGL();
	VOID showFPS(FLOAT);
	VOID shutdown();

	friend class App;

public:
	Graphics(HINSTANCE);
	~Graphics() { }

	CONST HWND &getHWND() const { return hWnd_; }
	CONST HINSTANCE &getHINSTANCE() const { return hInstance_; }

	VOID setNucleusColor(CONST Color4f &crColor) { nucleusColor_ = crColor; }
	VOID setElectronsColor(CONST Color4f &crColor) { electronsColor_ = crColor; }
	VOID setSphereColor(CONST Color4f &crColor) { sphereColor_ = crColor; }

	BOOL init(WNDPROC);
	VOID render(CONST Control&, CONST std::vector<nvec>&);
};

