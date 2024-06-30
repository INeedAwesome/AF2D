#pragma once

#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "AF2D/Event.h"

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

		bool PollEvent();
		AF::Event::Type GetEvent();
		void PushEvent(AF::Event::Type type);

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		bool IsOpen() { return !m_ShouldClose; }
		void Close();
		void Update();

	private:
		void InitOpenGL();

	private:
		Mode m_Mode;
		unsigned int m_Width;
		unsigned int m_Height;

		HWND m_WindowHandle;
		std::wstring m_Title;
		std::wstring m_ClassName;

		bool m_ShouldClose;

		std::vector<Event::Type> m_Events;

		HGLRC m_OpenGLRenderingContext;

	};

}
