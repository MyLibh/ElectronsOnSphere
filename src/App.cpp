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
	DBG("Running app");

	__int64 prevTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevTime));
	__int64 cps = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&cps));
	float spc = 1.0f / cps;

	MSG msg = { };
	while(WM_QUIT != msg.message && !GetAsyncKeyState(VK_ESCAPE))
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
			graphics_.render(control_, physics_.getPositions());
			graphics_.showFPS(dt);
			control_.manage();

			SwapBuffers(graphics_.hDC_);

			prevTime = cureTime;
		}
	}

	graphics_.shutdown();

	return static_cast<INT>(msg.wParam);
}

VOID App::update(FLOAT)
{
	physics_.doPhysics();
}

LRESULT App::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_SAVE:
			SaveConfig(physics_.getPositions());
			break;
		case ID_LOAD:
			physics_.load(LoadConfig("Save\\1.txt"));
			break;
		case ID_EXIT:
			PostQuitMessage(0);
			break;
		case ID_NUM:
			physics_.assignLocations(rand() % 10);
			break;

		default: return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

