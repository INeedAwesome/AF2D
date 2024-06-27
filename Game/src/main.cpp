#include <AF2D.h>

int Main()
{
	AF::Window window(L"2D Game", 900, 550, AF::Window::CUSTOM);

	AF::Event event;
	while (window.IsOpen())
	{
		while (window.PollEvent(event))
		{
			if (event.type == AF::Event::CLOSED)
				window.Close();
		}

		window.Update();
	}

	return 0;
}

#ifdef AF_DIST
int wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PWSTR, _In_ int)
{
	return Main();
}
#else
int main(int argc, char* argv[])
{
	return Main();
}
#endif
