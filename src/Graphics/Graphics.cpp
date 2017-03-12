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

	//HWND console = ::GetConsoleWindow();
	//::SetWindowPos(console, NULL, 0, 0, 700, 500, SWP_NOSIZE | SWP_NOZORDER);

	return nullptr;
}

//=====================================================================================================================

Graphics::Graphics(HINSTANCE hInst) :
	hWnd_(nullptr),
	hInstance_(hInst),
	hDC_(nullptr),
	hRC_(nullptr),
	width_(900),
	height_(900),
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
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);

	if(!RegisterClassEx(&wcex))
	{
		DBG("Failed to register the window class", DBGMODE::FAIL);

		return FALSE;
	}

	RECT rect = {0, 0, static_cast<long>(width_), static_cast<long>(height_)};
	AdjustWindowRect(&rect, wndStyle_, FALSE);

	auto width = rect.right - rect.left;
	auto height = rect.bottom - rect.top;
	auto x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	auto y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	hWnd_ = CreateWindowA("ElectronsOnSphere", title_.c_str(), wndStyle_, x, y, width, height, nullptr, nullptr, hInstance_, NULL);
	if(!hWnd_)
	{
		DBG("Failed to create the window", DBGMODE::FAIL);

		return FALSE;
	}

	ShowWindow(hWnd_, SW_SHOW);

	DBG("Ending OpenGl initialization", DBGMODE::STATUS);

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

	DBG("Ending OpenGl initialization", DBGMODE::STATUS);

	return TRUE;
}

VOID Graphics::shutdown()
{
	DBG("Starting shutdown", DBGMODE::STATUS);

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

VOID Graphics::render(CONST Control &crControl, CONST std::vector<nvec> &positions)
{
	DBG("Rendering");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glRotatef(crControl.angle, crControl.xrot, crControl.yrot, crControl.zrot);
	glPushMatrix();
	glTranslatef(crControl.xtr, crControl.ytr, crControl.ztr);

	static CONST FLOAT radius = 0.05f;
	GLUquadricObj *electron = gluNewQuadric();
	for(size_t i = 0; i < positions.size(); ++i)
	{
		glPushMatrix();
		glTranslatef(static_cast<FLOAT>(positions[i].getX()) - ((positions[i].getX() < 0)? -radius : radius),
                     static_cast<FLOAT>(positions[i].getY()) - ((positions[i].getY() < 0)? -radius : radius), 0.0f);
			glColor4f(electronsColor_); // Electron
			gluSphere(electron, radius, 100, 100);
		glPopMatrix();
	}
	gluDeleteQuadric(electron);

	GLUquadricObj *nucleus = gluNewQuadric();
	glColor4f(nucleusColor_); // The nucleus of an atom
	gluSphere(nucleus, radius * 4.0f, 200, 200);
	gluDeleteQuadric(nucleus);
	glPopMatrix();

	GLUquadricObj *sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	glColor4f(sphereColor_); // Sphere
	gluSphere(sphere, 1 - radius, 500, 500);
	gluDeleteQuadric(sphere);
	glPopMatrix();	

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



