#include <AF2D.h>

int main(int argc, char* argv[])
{
	AF::Window window(L"2D Game", 900, 550, AF::Window::FULLSCREEN);


	MSG msg;
	bool run = true;
	while (run)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				run = false;
			DispatchMessage(&msg);
			TranslateMessage(&msg);
		}

		window.Update();
	}


	return 0;
}