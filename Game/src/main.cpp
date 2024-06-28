#include <AF2D.h>

#include <iostream>

int Main()
{
	AF::Window window(L"2D Game", 1280, 720, AF::Window::CUSTOM);

	AF::Renderer::Init();
	AF::Renderer::SetScale(16);

	AF::Event event;
	while (window.IsOpen())
	{
		while (window.PollEvent(event))
		{
			if (event.type == AF::Event::CLOSED)
				window.Close();
			if (event.type == AF::Event::RESIZED)
				AF::Renderer::Resize(window.GetWidth(), window.GetHeight());
		}

		AF::Renderer::Begin();

		AF::Renderer::DrawQuad({ 2, 2 }, {1, 1});

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
