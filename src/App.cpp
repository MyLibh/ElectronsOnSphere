// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "App.hpp"

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
	float spc = 1.0f / cps;

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

			update(dt);
			graphics_.render(control_, physics_.getVector());
			graphics_.showFPS(dt);
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

void App::update(FLOAT)
{
	physics_.doPhysics();
}

LRESULT App::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
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

			if(GetSaveFileName(&of)) SaveConfig(filename, physics_.getVector(), physics_.getPotentialEnergy());

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

			if(GetOpenFileName(&of)) physics_.setVector(LoadConfig(filename));

			break;
		}
		case ID_EXIT:
			PostQuitMessage(0);
			break;

		case ID_NUMRAND:
			physics_.setVectorRandom(rand() % 15);
			break;
		case ID_NUMSET:
		{
			INT_PTR num = DialogBox(graphics_.getHINSTANCE(), MAKEINTRESOURCE(IDD_SETNUMBOX), hWnd, SetNumDialog);
			if(num >= 1) physics_.setVectorRandom(num);
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


