#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 
#include <Windows.h>

#include <glm/glm.hpp>

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2
#define MOUSE_BACK 3
#define MOUSE_FORWARD 4

namespace AF {
	
	class Input
	{
	public:
		static bool RegisterRawInput();
		static void HandleRawInput(WPARAM wParam, LPARAM lParam);
		static void HandleKeysInput(UINT msg, WPARAM wParam, LPARAM lParam);

		static bool WasKeyPressed(int keycode);
		static bool IsKeyPressed(int keycode);
		static bool WasMousePressed(int mousecode);
		static bool IsMousePressed(int mousecode);

		static glm::vec2 GetMousePositionDelta() { return s_MousePositionDelta; }
		static glm::vec2 GetMousePosition(HWND hwnd);
		static int GetMouseDeltaScroll() { return s_MouseScrollDelta; }

		static void ResetDeltas() { s_MousePositionDelta = {0, 0}; s_MouseScrollDelta = 0; s_MousePositionDeltaRead = true; s_MouseScrollDeltaRead = true; }

	private:
		static bool s_Keycodes[256];
		static bool s_MouseButtons[5];
		static int s_MouseScrollDelta;
		static glm::vec2 s_MousePositionDelta;
		static glm::vec2 s_MousePosition;

		// If we haven't read from these deltas, we want to add onto it not just set it. Because the input might be added more than once per frame
		static bool s_MousePositionDeltaRead;
		static bool s_MouseScrollDeltaRead;
	};

}


