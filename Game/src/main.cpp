#include <AF2D.h>

#include <iostream>

struct Quad {
	glm::vec2 Position;
	glm::vec2 Size;
};

int Main()
{
	AF::Window window(L"2D Game", 1280, 720, AF::Window::CUSTOM);

	AF::Renderer::Init();
	AF::Renderer::SetScale(16);

	AF::Texture2D texture; 
	texture.Init("assets/auge_512_512_BGRA_32BPP.png", AF::Texture2D::LINEAR);


	std::vector<Quad> quads;
	for (int i = 0; i < 100; i++)
	{
		Quad quad{};
		quad.Position = { i*2 , i*i};
		quad.Size = { i , i};
		quads.push_back(quad);
	}

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
		
		AF::Renderer::DrawQuad({ 1,0 }, {5, 4}, texture);

		for (Quad& quad : quads)
		{
			AF::Renderer::DrawQuad(quad.Position, quad.Size);
		}


		AF::Renderer::DrawQuad({ 0,0 }, {4, 4}, texture);

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
