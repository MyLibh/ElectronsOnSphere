#pragma once

#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include "Includes.hpp"
#include "Noncopyable.hpp"

namespace graphics 
{
	struct GraphicsManager
	{
		GLfloat x, y, z;
		GLfloat scale;
		GLfloat xrot, yrot, zrot;
	};

	class Graphics : public NoncopyableFull
	{
	private:
		static HGLRC                 hRC_;
		static PIXELFORMATDESCRIPTOR pfd_;
		static GraphicsManager       gm_;

	public:
		explicit Graphics() :
			NoncopyableFull()
		{ };

		~Graphics() { };

		static BOOL setWindowPixelFormatDescriptor(HDC);

		static VOID initGL(HDC);
		static VOID deleteGL();

		static VOID resize(INT, INT);

		static VOID display(/* CONST */);
		static VOID manage();
	};
} // namespace graphics

#endif // __GRAPHICS_HPP_INCLUDED__