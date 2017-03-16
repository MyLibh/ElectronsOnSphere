#pragma once

#include "Graphics\Graphics.hpp"
#include "Physics\Physics.hpp"
#include "Config.hpp"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK StdDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SetNumDialog(HWND hDlg, UINT msg, WPARAM wParam, LPARAM);

class App final : public NoncopyableFull
{
private:
	Graphics graphics_;
	physics::Physics  physics_;
	Control control_;

public:
	App(HINSTANCE);
	~App() { DBG("Closing app", DBGMODE::STATUS); }

	VOID update(FLOAT);
	INT run();
	BOOL init() { return graphics_.init(WndProc); };

	LRESULT wndProc(HWND, UINT, WPARAM, LPARAM);
};

Color4f GetChoosenColor(HWND);
