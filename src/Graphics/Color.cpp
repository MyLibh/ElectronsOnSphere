// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Color.hpp"

Color4f::Color4f(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha) :
	r(red),
	g(green),
	b(blue),
	a(alpha)
{ }

Color4f::Color4f(COLORREF color, FLOAT alpha) :
	r(GetRValue(color) / 255.0f),
	g(GetGValue(color) / 255.0f),
	b(GetBValue(color) / 255.0f),
	a(alpha)
{ }

Color4f::Color4f(CONST Color4f &crColor) :
	r(crColor.r),
	g(crColor.g),
	b(crColor.b),
	a(crColor.a)
{ }

Color4f& Color4f::operator=(CONST Color4f &crColor)
{
	r = crColor.r;
	g = crColor.g;
	b = crColor.b;
	a = crColor.a;

	return *this;
}

VOID glColor4f(CONST Color4f &crColor) { glColor4f(crColor.r, crColor.g, crColor.b, crColor.a); }

VOID glClearColor(CONST Color4f &crColor) { glClearColor(crColor.r, crColor.g, crColor.b, crColor.a); }