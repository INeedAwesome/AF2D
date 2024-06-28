#include <AF2D.h>

#include <iostream>

int Main()
{
	AF::Window window(L"2D Game", 1280, 720, AF::Window::CUSTOM);

	AF::Renderer::Init();

	AF::Event event;
	while (window.IsOpen())
	{
		while (window.PollEvent(event))
		{
			if (event.type == AF::Event::CLOSED)
				window.Close();
			if (event.type == AF::Event::RESIZED)
				std::cout << "Resized" << std::endl;
			//if (event.type == AF::Event::MOUSE_MOVE)
				//std::cout << "Mouse moved" << std::endl;
		}

		AF::Renderer::Begin();

		AF::Renderer::DrawQuad();

		AF::Renderer::End();

		window.Update();

		Sleep(1);
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
