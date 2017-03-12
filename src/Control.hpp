#pragma once

#include "Includes.hpp"

struct Control
{
	FLOAT xrot,
		  yrot,
		  zrot;

	FLOAT angle;

	FLOAT xtr,
		  ytr,
		  ztr;

	Control() :
		xrot(),
		yrot(0.5f),
		zrot(),
		angle(0.05f),
		xtr(),
		ytr(),
		ztr()
	{ }

	VOID manage()
	{
		static float d = 0.005f;

#define Key(param) GetAsyncKeyState(param)

		if     (Key(VK_RIGHT))  xtr += d;
		else if(Key(VK_LEFT))   xtr -= d;

		else if(Key(VK_UP))     ytr += d;
		else if(Key(VK_DOWN))   ytr -= d;

		else if(Key(VK_END))    ztr += d;
		else if(Key(VK_DELETE)) ztr -= d;


		else if(Key('A')) xrot -= d * 100;
		else if(Key('D')) xrot -= d * 10;

		else if(Key('W')) yrot += d * 100;
		else if(Key('S')) yrot -= d * 100;

		else if(Key('Q')) zrot += d * 100;
		else if(Key('E')) zrot -= d * 100;


		else if(Key('+')) angle += d * 10;
		else if(Key('-')) angle += d * 10;

#undef Key
	}
};
