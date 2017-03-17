#pragma once

#include "..\Includes.hpp"
#include "Graphics.hpp"
#include "..\Control.hpp"

Color4f GetChoosenColor(HWND);

INT_PTR CALLBACK StdDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SetNumDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SetDisplayDialog(HWND, UINT, WPARAM, LPARAM);