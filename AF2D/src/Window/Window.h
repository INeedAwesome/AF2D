#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <tchar.h>

namespace AF {
	class Window
	{
	public:
		enum Mode
		{
			CUSTOM,
			MAXIMIZED,
			FULLSCREEN
		};

		Window(const std::wstring& title, int width, int height, Mode mode = CUSTOM);
		~Window();

		void Update();

	private:
		Mode m_Mode;
		unsigned int m_Width;
		unsigned int m_Height;

		void* m_Data;

		HWND m_WindowHandle;
		std::wstring m_Title;
		std::wstring m_ClassName;

	};

}
