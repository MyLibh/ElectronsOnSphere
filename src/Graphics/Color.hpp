#pragma once

#include "..\Includes.hpp"

struct Color4f 
{
	FLOAT r,
		  g,
		  b, 
		  a;

	Color4f(FLOAT = 0.0f, FLOAT = 0.0f, FLOAT = 0.0f, FLOAT = 1.0f);
	Color4f(COLORREF, FLOAT = 1.0f);
	Color4f(CONST Color4f&);

	Color4f& operator=(CONST Color4f&);

	BOOL operator==(CONST Color4f&) const;
	BOOL operator!=(CONST Color4f&) const;
};

VOID glColor4f(CONST Color4f&);
VOID glClearColor(CONST Color4f&);