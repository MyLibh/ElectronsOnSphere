#include "Graphics.hpp"

namespace graphics
{
	HGLRC Graphics::hRC_ = nullptr;

	PIXELFORMATDESCRIPTOR Graphics::pfd_ = { sizeof(PIXELFORMATDESCRIPTOR) };

	GraphicsManager Graphics::gm_ = { };

	BOOL Graphics::setWindowPixelFormatDescriptor(HDC hDC)
	{
		INT pfdIndex = 0;

		pfd_.nVersion        =  1;
		pfd_.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd_.iPixelType      = PFD_TYPE_RGBA;
		pfd_.cColorBits      = 32;
		pfd_.cRedBits        =  8;
		pfd_.cGreenBits      =  8;
		pfd_.cGreenShift     =  8;
		pfd_.cBlueBits       =  8;
		pfd_.cAccumBits      = 64;
		pfd_.cAccumRedBits   = 16;
		pfd_.cAccumGreenBits = 16;
		pfd_.cAccumBlueBits  = 16;
		pfd_.cDepthBits      = 32;
		pfd_.cStencilBits    =  8;
		pfd_.iLayerType      = PFD_MAIN_PLANE;

		pfdIndex = ChoosePixelFormat(hDC, &pfd_);
		if(!pfdIndex)
		{
			pfdIndex = 1;
			if(!DescribePixelFormat(hDC, pfdIndex, sizeof(PIXELFORMATDESCRIPTOR), &pfd_)) return FALSE;
		}

		if(!SetPixelFormat(hDC, pfdIndex, &pfd_)) return FALSE;
		return TRUE;
	}

	VOID Graphics::manage()
	{
		if(GetAsyncKeyState(VK_UP)) gm_.y += 0.1;
		else if(GetAsyncKeyState(VK_DOWN)) gm_.y -= 0.1;
		else if(GetAsyncKeyState(VK_LEFT)) gm_.x -= 0.1;
		else if(GetAsyncKeyState(VK_RIGHT)) gm_.x += 0.1;
		else if(GetAsyncKeyState('+')) gm_.scale += 0.1;
		else if(GetAsyncKeyState('-')) gm_.scale -= 0.1;
		else if(GetAsyncKeyState('1')) gm_.xrot++;
		else if(GetAsyncKeyState('3')) gm_.yrot++;
		else if(GetAsyncKeyState('5')) gm_.zrot++;
	}

	VOID Graphics::initGL(HDC hDC)
	{
		static float pos[4] = { 3, 3, 3, 1 };
		static float dir[3] = { -1, -1, -1 };
		
		setWindowPixelFormatDescriptor(hDC);
		
		hRC_ = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC_);

		glClearColor(1.0, 1.0, 1.0, 0.0);

		glEnable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	}

	VOID Graphics::deleteGL()
	{
		if(hRC_)
		{
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(hRC_);
		}
	}

	VOID Graphics::resize(INT width, INT height)
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-5, 5, -5, 5, 2, 12);
		glMatrixMode(GL_MODELVIEW);
	}

	VOID Graphics::display() 
	{
		glColor3f(1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslatef(gm_.x, gm_.y, gm_.z);
		//glScalef(gm_.scale, gm_.scale, gm_.scale);
		//glRotatef(1, gm_.xrot, gm_.yrot, gm_.zrot);

		glBegin(GL_LINES);
		glRotatef(50, 100, 45, 45);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 100);

			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 100, 0);

			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0, 0, 0);
			glVertex3f(100, 0, 0);

			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0, 0, 0);
			glVertex3f(100, 100, 100);
		glEnd();
		
		glFinish();
		SwapBuffers(wglGetCurrentDC());
	}
}; // namespace graphics