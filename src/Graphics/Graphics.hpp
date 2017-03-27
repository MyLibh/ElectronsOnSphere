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

VOID BuildFont(HDC);

typedef nvector NVECTOR;
typedef crnvector CRNVECTOR;

class Graphics final : public NoncopyableFull
{
public:
	static CONST SIZE_T NUMBER_OF_ELEMENTS = 9;

private:
	HWND        hWnd_;
	HINSTANCE   hInstance_;
	HDC         hDC_;
	HGLRC       hRC_;
	static UINT width_,
		        height_;
	std::string title_;
	FLOAT       fps_;
	DWORD       wndStyle_;

	Color4f     nucleusColor_,
				electronsColor_,
				sphereColor_;

	static BOOL visibility_[NUMBER_OF_ELEMENTS];

	BOOL initWindow(WNDPROC);
	BOOL initGL();

	static VOID drawText(CONST std::string&);

public:
	static CONST UINT base_;

	Graphics(HINSTANCE);
	~Graphics() { }

	enum VISINDEX
	{
		ALFA = 0,
		ROTX,
		ROTY,
		ROTZ,
		TRX,
		TRY,
		TRZ,
		ENERGY,
		COORDS
	};

	static BOOL getVisibility(SIZE_T index) { return visibility_[index]; }

	CONST HWND      &getHWND()      const { return hWnd_; }
	CONST HINSTANCE &getHINSTANCE() const { return hInstance_; }
	CONST HDC       &getHDC()       const { return hDC_; }

	static VOID setVisibility(SIZE_T index, BOOL show) { visibility_[index] = show; }

	VOID setNucleusColor(CONST Color4f &crColor)   { if(crColor != DO_NOT_CHANGE_COLOR) nucleusColor_   = crColor; }
	VOID setElectronsColor(CONST Color4f &crColor) { if(crColor != DO_NOT_CHANGE_COLOR) electronsColor_ = crColor; }
	VOID setSphereColor(CONST Color4f &crColor)    { if(crColor != DO_NOT_CHANGE_COLOR) sphereColor_    = crColor; }
	
	static VOID drawInfo(CONST Control&, SIZE_T, DOUBLE);

	BOOL init(WNDPROC);
	VOID render(CONST Control&, CRNVECTOR);
	VOID showFPS(FLOAT);
	VOID shutdown();	
};

VOID DeleteFont();
