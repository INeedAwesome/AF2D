#include "afpch.h"
#include "Window.h"

#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <glad/glad.h>

#include "AF2D/Input/Input.h"

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

AF::Window::Window(const std::wstring& title, int width, int height, Mode mode)
	: m_WindowHandle(0), m_ShouldClose(false), m_Events()
{
	m_Title = title;
	m_ClassName = title + L"AF2DApp";
	m_Width = width;
	m_Height = height;
	m_Mode = mode;

	bool custom = false;
	bool maximized = false;
	bool fullscreen = false;
	DWORD style = WS_OVERLAPPEDWINDOW;
	RECT rect{};

	// Calculate the correct width and height depending on the mode
	switch (mode)
	{
	case Window::CUSTOM:
		custom = true;
		rect.right = m_Width;
		rect.bottom = m_Height;
		AdjustWindowRect(&rect, style, FALSE);
		break;

	case Window::MAXIMIZED:
		maximized = true;
		rect.right = m_Width;
		rect.bottom = m_Height;
		AdjustWindowRect(&rect, style, FALSE);
		break;

	case Window::FULLSCREEN:
		fullscreen = true;
		style = WS_VISIBLE;
		rect.right = m_Width;
		rect.bottom = m_Height;
		break;
	}

	rect.right = rect.right - rect.left;
	rect.bottom = rect.bottom - rect.top;

	// Register the window class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW;
	wcex.lpfnWndProc = &WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = LoadIcon(GetModuleHandle(nullptr), IDI_WINLOGO);
	wcex.hIconSm = LoadIcon(GetModuleHandle(nullptr), IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = m_ClassName.c_str();
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(0, L"Could not register the window class!", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	// Create the window
	m_WindowHandle = CreateWindowEx(0, m_ClassName.c_str(), m_Title.c_str(), style,
		//0, 0, rect.right, rect.bottom,
		custom ? CW_USEDEFAULT : rect.left, custom ? CW_USEDEFAULT : rect.top, rect.right, rect.bottom,
		NULL,NULL, GetModuleHandle(nullptr), this
	);

	if (!m_WindowHandle)
	{
		MessageBox(NULL, L"Could not create the window!", L"Error", NULL);
		return;
	}

	// https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/apply-rounded-corners
	DWM_WINDOW_CORNER_PREFERENCE attr = DWMWCP_ROUNDSMALL;
	DwmSetWindowAttribute(m_WindowHandle, DWMWA_WINDOW_CORNER_PREFERENCE , &attr, sizeof(DWM_WINDOW_CORNER_PREFERENCE));

	InitOpenGL();

	if (fullscreen)
	{
		int monitorWidth = GetSystemMetrics(SM_CXSCREEN);
		int monitorHeight = GetSystemMetrics(SM_CYSCREEN);
		style = WS_VISIBLE;
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, style);
		m_Width = monitorWidth;
		m_Height = monitorHeight;
		SetWindowPos(m_WindowHandle, 0, 0, 0, m_Width, m_Height, SWP_SHOWWINDOW);
	}

	ShowWindow(m_WindowHandle, maximized ? SW_SHOWMAXIMIZED : SW_SHOW);

	UpdateWindow(m_WindowHandle);

	m_WindowDeviceContext = GetDC(m_WindowHandle);
}

AF::Window::~Window()
{
	ReleaseDC(m_WindowHandle, m_WindowDeviceContext);
	DestroyWindow(m_WindowHandle);
	UnregisterClass(m_ClassName.c_str(), GetModuleHandle(nullptr));
}

void AF::Window::Close()
{
	m_ShouldClose = true; 
}

bool AF::Window::PollEvent()
{
	MSG msg;
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
		return true;
	}
	return false;
}

void AF::Window::UpdateWidthHeight()
{
	RECT rect;
	GetClientRect(m_WindowHandle, &rect);
	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;
}

void AF::Window::Update()
{
	SwapBuffers(m_WindowDeviceContext);
}

AF::Event::Type AF::Window::GetEvent()
{
	Event event { Event::NONE };
	int index = (int)m_Events.size() - 1;
	if (index < 0)
		return event.type;
	
	event.type = m_Events[index];
	m_Events.pop_back();

	return event.type;
}

void AF::Window::PushEvent(AF::Event::Type type)
{
	m_Events.push_back(type);
}

void AF::Window::InitOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC deviceContext = GetDC(m_WindowHandle);

	int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
	if (pixelFormat == 0)
	{
		std::cout << "Pixel format could not be chosen!" << std::endl;
		return;
	}
	SetPixelFormat(deviceContext, pixelFormat, &pfd);

	m_OpenGLRenderingContext = wglCreateContext(deviceContext);
	if (m_OpenGLRenderingContext == NULL)
	{
		std::cout << "m_OpenGLRenderingContext was NULL!" << std::endl;
		return;
	}
	if (wglMakeCurrent(deviceContext, m_OpenGLRenderingContext) == FALSE)
	{
		std::cout << "Could not make context current!" << std::endl;
		return;
	}

	gladLoadGL();
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static AF::Window* thisWindow= nullptr;

	switch (msg)
	{
	case WM_CREATE: 
	{
		CREATESTRUCT* ptrCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		thisWindow = reinterpret_cast<AF::Window*>(ptrCreate->lpCreateParams);
		break;
	}
	case WM_DESTROY:
		thisWindow->PushEvent(AF::Event::CLOSED);
		break;

	case WM_SIZE:
		thisWindow->PushEvent(AF::Event::RESIZED);
		thisWindow->UpdateWidthHeight();
		break;

	case WM_MOUSEMOVE:
		thisWindow->PushEvent(AF::Event::MOUSE_MOVE);
		break;

	case WM_KEYUP:
	case WM_KEYDOWN:
		AF::Input::HandleKeysInput(msg, wParam, lParam);
		break;

	case WM_INPUT:
		AF::Input::HandleRawInput(wParam, lParam);
		if (GET_RAWINPUT_CODE_WPARAM(wParam) == RIM_INPUT)
			DefWindowProc(hwnd, msg, wParam, lParam);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}
