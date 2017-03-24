// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Graphics.hpp"

HWND InitConsole(ConsoleMode mode)
{
	if(::AllocConsole())
	{
		INT hCrt = _open_osfhandle(reinterpret_cast<INT_PTR>(GetStdHandle(STD_OUTPUT_HANDLE)), _O_TEXT);
		if(!hCrt) return FALSE;

		if(mode == ConsoleMode::CM_ALL    || mode == ConsoleMode::CM_OUT ||
		   mode == ConsoleMode::CM_IN_OUT || mode == ConsoleMode::CM_OUT_ERROR)
		{
			*stdout = *::_fdopen(hCrt, "w");
			::setvbuf(stdout, nullptr, _IONBF, 0);
		}

		if(mode == ConsoleMode::CM_ALL      || mode == ConsoleMode::CM_ERROR ||
		   mode == ConsoleMode::CM_IN_ERROR || mode == ConsoleMode::CM_OUT_ERROR)
		{
			*stderr = *::_fdopen(hCrt, "w");
			::setvbuf(stderr, nullptr, _IONBF, 0);
		}

		if(mode == ConsoleMode::CM_ALL    || mode == ConsoleMode::CM_IN ||
		   mode == ConsoleMode::CM_IN_OUT || mode == ConsoleMode::CM_IN_ERROR)
		{
			*stdin = *::_fdopen(hCrt, "r");
			::setvbuf(stdin, nullptr, _IONBF, 0);
		}
		std::ios::sync_with_stdio();
	}
	else return FALSE;

	HWND console = GetConsoleWindow();
	SetWindowPos(console, nullptr, 0, 0, 700, 500, SWP_NOSIZE | SWP_NOZORDER);

	return nullptr;
}

//=====================================================================================================================

UINT Graphics::width_  = 900;
UINT Graphics::height_ = 900;

UINT Graphics::base_ = 0;

BOOL Graphics::visibility_[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

Graphics::Graphics(HINSTANCE hInst) :
	hWnd_(nullptr),
	hInstance_(hInst),
	hDC_(nullptr),
	hRC_(nullptr),
	title_("Electrons on sphere"),
	fps_(0.0f),
	wndStyle_(WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX),
	nucleusColor_(1.0f, 0.0f, 0.0f, 1.0f),
	electronsColor_(1.0f, 0.0f, 0.0f, 1.0f),
	sphereColor_(1.0f, 0.0f, 0.5f, 0.1f)
{ }

BOOL Graphics::initWindow(WNDPROC wndFunc)
{
	DBG("Starting window initialization", DBGMODE::STATUS);

	WNDCLASSEX wcex    = { sizeof(WNDCLASSEX) };
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance     = hInstance_;
	wcex.lpfnWndProc   = wndFunc;
	wcex.hIcon         = LoadIcon(hInstance_, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	wcex.lpszClassName = "ElectronsOnSphere";
    wcex.hIconSm       = LoadIcon(hInstance_, MAKEINTRESOURCE(IDI_ICON));
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);

	if(!RegisterClassEx(&wcex))
	{
		DBG("Failed to register the window class", DBGMODE::FAIL);

		return FALSE;
	}

	RECT rect = {0, 0, static_cast<long>(Graphics::width_), static_cast<long>(Graphics::height_)};
	AdjustWindowRect(&rect, wndStyle_, FALSE);

	auto width = rect.right - rect.left;
	auto height = rect.bottom - rect.top;
	auto x = (GetSystemMetrics(SM_CXSCREEN) -  width) / 2;
	auto y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	hWnd_ = CreateWindowA("ElectronsOnSphere", title_.c_str(), wndStyle_, x, y, width, height, nullptr, nullptr, hInstance_, NULL);
	if(!hWnd_)
	{
		DBG("Failed to create the window", DBGMODE::FAIL);

		return FALSE;
	}

	ShowWindow(hWnd_, SW_SHOW);

	DBG("Ending window initialization", DBGMODE::STATUS);

	return TRUE;
}

BOOL Graphics::initGL()
{
	DBG("Starting OpenGl initialization", DBGMODE::STATUS);
	hDC_ = GetDC(hWnd_);

	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };
	pfd.nVersion              = 1;
	pfd.dwFlags               = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType            = PFD_TYPE_RGBA;
	pfd.cColorBits            = 32;
	pfd.cDepthBits            = 24;
	pfd.cStencilBits          = 8;

	INT format = ChoosePixelFormat(hDC_, &pfd);
	if(!SetPixelFormat(hDC_, format, &pfd))
	{
		DBG("Faled to set pixel format", DBGMODE::FAIL);

		return FALSE;
	}

	hRC_ = wglCreateContext(hDC_);
	if(!wglMakeCurrent(hDC_, hRC_))
	{
		DBG("Failed to activate render context", DBGMODE::FAIL);

		return FALSE;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	FLOAT pos[4] = { 3, 3, 3, 1 };
    FLOAT dir[3] = { -1, -1, -1 };

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	BuildFont(hDC_);

	DBG("Ending OpenGl initialization", DBGMODE::STATUS);

	return TRUE;
}

VOID Graphics::shutdown()
{
	DBG("Starting shutdown", DBGMODE::STATUS);

	DeleteFont();
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(hRC_);
	ReleaseDC(hWnd_, hDC_);

	DBG("Ending shutdown", DBGMODE::STATUS);
}

BOOL Graphics::init(WNDPROC wndFunc)
{
	DBG("Starting initialization", DBGMODE::STATUS);

	if(!initWindow(wndFunc)) return FALSE;
	if(!initGL())            return FALSE;

	DBG("Ending initialization", DBGMODE::STATUS);

	return TRUE;
}

VOID Graphics::showFPS(FLOAT dt)
{
	static FLOAT elapsed    = 0;
	static INT   frameCount = 0;

	elapsed += dt;
	frameCount++;
	if(elapsed >= 1.0f)
	{
		fps_ = static_cast<FLOAT>(frameCount);

		std::stringstream sstr;
		sstr << title_ << ", FPS: " << fps_;

		SetWindowText(hWnd_, sstr.str().c_str());

		elapsed = 0.0f;
		frameCount = 0;
	}
}

VOID Graphics::render(CONST Control &crControl, std::vector<nvec> crPositions)
{
	DBG("Rendering");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(crControl.angle, crControl.xrot, crControl.yrot, crControl.zrot);
	glPushMatrix();
	glTranslatef(crControl.xtr, crControl.ytr, crControl.ztr);

	static CONST FLOAT radius = 0.05f;
	GLUquadricObj *electron = gluNewQuadric();
	for(auto pos : crPositions)
	{
		glPushMatrix();
		glTranslatef(static_cast<FLOAT>(pos.getX()) - ((pos.getX() < 0)? -radius : radius),
                     static_cast<FLOAT>(pos.getY()) - ((pos.getY() < 0)? -radius : radius),
                     static_cast<FLOAT>(pos.getZ()) - ((pos.getZ() < 0)? -radius : radius));
			glColor4f(electronsColor_); // Electron
			gluSphere(electron, radius, 100, 100);
		glPopMatrix();
	}
	gluDeleteQuadric(electron);

	GLUquadricObj *nucleus = gluNewQuadric();
	glColor4f(nucleusColor_); // The nucleus of an atom
	gluSphere(nucleus, radius * 4.0f, 200, 200);
	gluDeleteQuadric(nucleus);

	GLUquadricObj *sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	glColor4f(sphereColor_); // Sphere
	gluSphere(sphere, 1 - radius, 500, 500);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	if(Graphics::visibility_[Graphics::NUMBER_OF_ELEMENTS - 1])
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -1.0f);
		glLineWidth(5.0f);
		glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f); // X-axis
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 1.0f); // Y-axis
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f); // Z-axis
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
		glPopMatrix();
	}

	Graphics::drawInfo(crControl, crPositions.size());
}

VOID Graphics::drawInfo(CONST Control &crControl, SIZE_T num)
{
	glPushMatrix();
	glLoadIdentity();

	FLOAT x = -0.99f,
		  y =  0.95f,
		  z = -1.0f;

	static CONST FLOAT dy = 0.05f;

	std::string info[Graphics::NUMBER_OF_ELEMENTS] =
	{
		"Alfa: ",
		"Rotation X: ",
		"Rotation Y: ",
		"Rotation Z: ",
		"Translation X: ",
		"Translation Y: ",
		"Translation Z: ",
		"Potential Energy: ",
		"Electrons: "
	};

	/*info[0] += std::to_string(crControl.angle);
	info[1] += std::to_string(crControl.xrot);
	info[2] += std::to_string(crControl.yrot);
	info[3] += std::to_string(crControl.zrot);
	info[4] += std::to_string(crControl.xtr);
	info[5] += std::to_string(crControl.ytr);
	info[6] += std::to_string(crControl.ztr);
	info[7] += std::to_string(0);
	info[8] += std::to_string(num);   */

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for(SIZE_T i = 0; i < Graphics::NUMBER_OF_ELEMENTS; ++i)
		if(Graphics::visibility_[i] || i == Graphics::NUMBER_OF_ELEMENTS - 1)
		{
			glRasterPos3f(x, y, z);
			Graphics::drawText(info[i]);

			y -= dy;
		}

	glPopMatrix();
}

VOID Graphics::drawText(CONST std::string &crText)
{
	glPushAttrib(GL_LIST_BIT);
	glListBase(Graphics::base_ - 32);
	glCallLists(crText.length(), GL_UNSIGNED_BYTE, crText.c_str());
	glPopAttrib();
}

VOID BuildFont(HDC hDC)
{
	Graphics::base_ = glGenLists(96);

	HFONT font = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Courier New");

	SelectObject(hDC, font);
	wglUseFontBitmaps(hDC, 32, 96, Graphics::base_);
}

VOID DeleteFont() { glDeleteLists(Graphics::base_, 96); }




