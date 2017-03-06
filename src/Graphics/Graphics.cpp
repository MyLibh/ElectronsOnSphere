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

HWND CreateTrackBar(HWND hWnd, UINT min, UINT max, UINT minSel, UINT maxSel)
{
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

Graphics::~Graphics()
{
}

INT Graphics::run()
{
	DBG("Running app");

	__int64 prevTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevTime));
	__int64 cps = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&cps));
	float spc = 1.0f / cps;

	MSG msg = { };
	while(WM_QUIT != msg.message)
	{
		if(PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			__int64 cureTime = 0;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&cureTime));
			FLOAT dt = (cureTime - prevTime) * spc;

			update(dt);
			render();
			FPS(dt);

			SwapBuffers(hDC_);

			prevTime = cureTime;
		}
	}

	shutdown();

	return static_cast<INT>(msg.wParam);
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

	RECT rect = {0, 0, width_, height_};
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
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glLightfv(GL_LIGHT0, GL_POSITION, pos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	/*if(glewInit())
	{
		std::cerr << "Failed to init GLEW\n";

		return FALSE;
	}*/
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

VOID Graphics::FPS(FLOAT dt)
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

VOID Graphics::update(FLOAT)
{
	DBG("Rendering");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);
	glEnd();

	glPushMatrix();
		static FLOAT angle = 0.5f;
		
		glColor4f(1.0f, 0.0f, 0.5f, 1.0f);
		static GLUquadricObj *sphere = gluNewQuadric();
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		gluSphere(sphere, 0.5, 100, 100);
	glPopMatrix();
}

VOID Graphics::render()
{
	
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

	return 0;
}

