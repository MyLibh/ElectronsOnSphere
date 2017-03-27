#pragma once

#include "Graphics\Graphics.hpp"
#include "Physics\Physics.hpp"
#include "Graphics\Dialogs.hpp"
#include "Config.hpp"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class App final : public NoncopyableFull
{
private:
	Graphics graphics_;
	PHYSICS::Physics  physics_;
	Control control_;

public:
	App(HINSTANCE);
	~App() { DBG("Closing app", DBGMODE::STATUS); }

	INT run();
	BOOL init() { return graphics_.init(WndProc); };

	LRESULT wndProc(HWND, UINT, WPARAM, LPARAM);
};

HWND CreateTrackbar(HINSTANCE, HWND, UINT, UINT, UINT, UINT);

