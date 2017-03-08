#include "Graphics.hpp"

namespace
{
	Graphics *gpApp = nullptr;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(gpApp) return gpApp->wndProc(hWnd, msg, wParam, lParam);
	else return DefWindowProc(hWnd, msg, wParam, lParam);
}

//=====================================================================================================================

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
	wndStyle_(WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX)
{
	gpApp = this;
}

BOOL Graphics::initWindow()
{
	DBG("Starting window initialization");

	WNDCLASSEX wcex    = { sizeof(WNDCLASSEX) };
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance     = hInstance_;
	wcex.lpfnWndProc   = WndProc;
	wcex.hIcon         = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	wcex.lpszClassName = "ElectronsOnSphere";
    wcex.hIconSm       = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_ICON));
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

	//InitConsole();
	ShowWindow(hWnd_, SW_SHOW);

	DBG("Ending OpenGl initialization");

	return TRUE;
}

BOOL Graphics::initGL()
{
	DBG("Starting OpenGl initialization");
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

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);

	DBG("Ending OpenGl initialization");

	return TRUE;
}

VOID Graphics::shutdown()
{
	DBG("Starting shutdown");

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(hRC_);
	ReleaseDC(hWnd_, hDC_);

	DBG("Ending shutdown");
}

BOOL Graphics::init()
{
	DBG("Starting initialization");

	if(!initWindow()) return FALSE;
	if(!initGL())     return FALSE;

	DBG("Ending initialization");

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

VOID Graphics::render(CONST std::vector<nvec> &positions)
{
	DBG("Rendering");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLUquadricObj *electron = gluNewQuadric();
	for(size_t i = 0; i < positions.size(); ++i)
	{
		glPushMatrix();
		glTranslatef(static_cast<FLOAT>(positions[i].getX()), static_cast<FLOAT>(positions[i].getY()), static_cast<FLOAT>(0));
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // Electron
			gluSphere(electron, 0.05, 100, 100);
		glPopMatrix();
	}
	gluDeleteQuadric(electron);

	GLUquadricObj *nucleus = gluNewQuadric();
	gluQuadricDrawStyle(nucleus, GLU_LINE);
	glColor4f(1.0f, 0.0f, 0.5f, 1.0f); // The nucleus of an atom
	gluSphere(nucleus, 1, 500, 500);
	gluDeleteQuadric(nucleus);

	/*glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f); // X-axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f); // Y-axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f); // Z-axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();*/
}

LRESULT Graphics::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_SAVE:
			break;
		case ID_LOAD:
			break;
		case ID_EXIT:
			PostQuitMessage(0);
			break;

		default: break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

