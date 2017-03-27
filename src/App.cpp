// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "App.hpp"

#define ID_TRACKBAR 0

namespace
{
	App *gpApp = nullptr;
};

 LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return ((gpApp)? gpApp->wndProc(hWnd, msg, wParam, lParam) : DefWindowProc(hWnd, msg, wParam, lParam)); }

App::App(HINSTANCE hInstance) :
	graphics_(hInstance),
	physics_(),
	control_()
{ gpApp = this; }

INT App::run()
{
	DBG("Running app", DBGMODE::STATUS);

	__int64 prevTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevTime));
	__int64 cps = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&cps));
	FLOAT spc = 1.0f / cps;

	HWND hTrack = CreateTrackbar(graphics_.getHINSTANCE(), graphics_.getHWND(), 0, 10, 10, 10);
	MSG msg = { };
	while(msg.message != WM_QUIT && !GetAsyncKeyState(VK_ESCAPE))
	{
		if(PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			__int64 cureTime = 0;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&cureTime));
			FLOAT dt = (cureTime - prevTime) * spc;
			graphics_.showFPS(dt);

			physics_.doPhysics();
			graphics_.render(control_, physics_.getPositions());
			Graphics::drawInfo(control_, physics_.getPositions().size(), physics_.getPotentialEnergy());	
			control_.manage();

			SwapBuffers(graphics_.getHDC());
			prevTime = cureTime;
		}
	}

	ShowWindow(graphics_.getHWND(), SW_HIDE);
	SetFocus(GetConsoleWindow());

	graphics_.shutdown();

	return static_cast<INT>(msg.wParam);
}

LRESULT App::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_SIZE:
	{
		INT nWidth  = LOWORD(lParam);		
		INT nHeight = HIWORD(lParam);		
		glViewport(0, 0, nWidth, nHeight);	

		glMatrixMode(GL_PROJECTION);		
		glLoadIdentity();					

		gluPerspective(45.0f, static_cast<DOUBLE>(nWidth) / static_cast<DOUBLE>(nHeight), 0.1f, 100.0f);

		break;
	}	
	case WM_COMMAND:
	{
		switch(LOWORD(wParam))
		{
		case ID_MANAGMENTHELP:
			DialogBox(graphics_.getHINSTANCE(), MAKEINTRESOURCE(IDD_HELPBOX), hWnd, StdDialog);
            break;
		case ID_ABOUT:
			DialogBox(graphics_.getHINSTANCE(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, StdDialog);
            break;
		case ID_SAVE:
		{
			CHAR filename[MAX_PATH] = "";

			OPENFILENAME of = { OPENFILENAME_SIZE_VERSION_400A };
			of.hwndOwner    = graphics_.getHWND();
			of.lpstrFilter  = "Text Files (*.txt)\0";
			of.lpstrFile    = filename;
			of.nMaxFile     = MAX_PATH;
			of.Flags        = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			of.lpstrDefExt  = "txt";

			if(GetSaveFileName(&of)) SaveConfig(filename, physics_.getPositions(), physics_.getPotentialEnergy());

			break;
		}
		case ID_LOAD:
		{
			CHAR filename[MAX_PATH] = "";

			OPENFILENAME of    = { OPENFILENAME_SIZE_VERSION_400A };
			of.hwndOwner       = graphics_.getHWND();
			of.hInstance       = graphics_.getHINSTANCE();
			of.lpstrFilter     = "Text Files only(*.txt*)\0*.txt*\0";
			of.nFilterIndex    = 1;
			of.lpstrFile       = filename;
			of.nMaxFile        = MAX_PATH;
			of.lpstrInitialDir = nullptr;
			of.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			if(GetOpenFileName(&of)) physics_.setPositions(LoadConfig(filename));

			break;
		}
		case ID_EXIT:
			PostQuitMessage(0);
			break;

		case ID_NUMRAND:
			physics_.setPositionsRandom(rand() % 15);
			break;
		case ID_NUMSET:
		{
			INT_PTR num = DialogBox(graphics_.getHINSTANCE(), MAKEINTRESOURCE(IDD_SETNUMBOX), hWnd, SetNumDialog);
			if(num >= 1) physics_.setPositionsRandom(num);
			break;
		}

		case ID_COLORBCKGRND:
			glClearColor(GetChoosenColor(graphics_.getHWND()));
			break;
		case ID_COLRNUCLEUS:
			graphics_.setNucleusColor(GetChoosenColor(graphics_.getHWND()));
			break;
		case ID_COLORELECTORNS:
			graphics_.setElectronsColor(GetChoosenColor(graphics_.getHWND()));
			break;
		case ID_COLORSPHERE:
			graphics_.setSphereColor(GetChoosenColor(graphics_.getHWND()));
			break;

		case ID_DISPLAY:
			DialogBox(graphics_.getHINSTANCE(), MAKEINTRESOURCE(IDD_DISPLAY), hWnd, SetDisplayDialog);
			break;

		default: return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

HWND CreateTrackbar(HINSTANCE hInstance, HWND hwndDlg, UINT iMin, UINT iMax, UINT iSelMin, UINT iSelMax)  
{ 
    //InitCommonControls();

    HWND hwndTrack = CreateWindowEx( 0, TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE, 0, 0, 400, 450, hwndDlg, ID_TRACKBAR, hInstance, NULL); 

    SendMessage(hwndTrack, TBM_SETRANGE,    static_cast<WPARAM>(TRUE),  static_cast<LPARAM>(MAKELONG(iMin, iMax)));      
    SendMessage(hwndTrack, TBM_SETPAGESIZE, static_cast<WPARAM>(FALSE), static_cast<LPARAM>(4));  
    SendMessage(hwndTrack, TBM_SETSEL,      static_cast<WPARAM>(FALSE), static_cast<LPARAM>(MAKELONG(iSelMin, iSelMax))); 
    SendMessage(hwndTrack, TBM_SETPOS,      static_cast<WPARAM>(TRUE),  static_cast<LPARAM>(iSelMin)); 

    SetFocus(hwndTrack); 

    return hwndTrack; 
} 


