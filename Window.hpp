#pragma once

#ifndef __WINDOW_HPP_INCLUDED__
#define __WINDOW_HPP_INCLUDED__

#include "Includes.hpp"
#include "Graphics.hpp"

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

HWND             InitConsole(ConsoleMode);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
INT              StartDialog(HINSTANCE);

#endif // __WINDOW_HPP_INCLUDED__