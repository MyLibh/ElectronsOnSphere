#include "App.hpp"

App::App(HINSTANCE hInstance) :
	graphics_(hInstance),
	physics_() 
{ }

INT App::run()
{
	DBG("Running app");

	__int64 prevTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevTime));
	__int64 cps = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&cps));
	float spc = 1.0f / cps;

	MSG msg = { };
	while(WM_QUIT != msg.message)
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
			graphics_.render();
			graphics_.showFPS(dt);

			SwapBuffers(graphics_.hDC_);

			prevTime = cureTime;
		}
	}

	graphics_.shutdown();

	return static_cast<INT>(msg.wParam);
}

VOID App::update(FLOAT)
{
	//Physics
	//physics_.doPysics();
}
