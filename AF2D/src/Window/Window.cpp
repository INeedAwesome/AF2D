#include "afpch.h"
#include "Window.h"

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

AF::Window::Window(const std::wstring& title, int width, int height, Mode mode)
{
	m_Title = title;
	m_ClassName = title + L"AF2DApp";
	m_Width = width;
	m_Height = height;

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
		NULL,NULL, GetModuleHandle(nullptr), NULL
	);

	if (!m_WindowHandle)
	{
		MessageBox(NULL, L"Could not create the window!", L"Error", NULL);
		return;
	}

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
	
}

AF::Window::~Window()
{
}

void AF::Window::Update()
{
	UpdateWindow(m_WindowHandle);
}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}