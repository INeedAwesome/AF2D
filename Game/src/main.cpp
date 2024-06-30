#include <AF2D.h>

#include <iostream>

struct Quad {
	glm::vec3 Position;
	glm::vec2 Size;
};

int Main()
{
	AF::Window window(L"2D Game", 1280, 720, AF::Window::CUSTOM);

	AF::Input::RegisterRawInput();

	AF::Renderer::Init();
	AF::Renderer::SetScale(16);
	AF::Renderer::Resize(window.GetWidth(), window.GetHeight());

	AF::Texture2D playerTexture; 
	playerTexture.Init("assets/gruminion.png", AF::Texture2D::LINEAR);

	AF::Texture2D grassTexture;
	grassTexture.Init("assets/grass.png", AF::Texture2D::NEAREST);


	std::vector<Quad> quads;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			Quad quad{};
			quad.Position = { i, j, 0};
			quad.Size = { 1 , 1 };
			quads.push_back(quad);
		}
	}

	Quad playerQuad;
	playerQuad.Position = { 8, 8, 1};
	playerQuad.Size = { 1, 1 };

	while (window.IsOpen())
	{
		while (window.PollEvent())
		{
			AF::Event::Type event = window.GetEvent(); 
			if (event == AF::Event::CLOSED)
				window.Close();
			if (event == AF::Event::RESIZED)
				AF::Renderer::Resize(window.GetWidth(), window.GetHeight());
		}

		if (AF::Input::IsKeyPressed('W'))
			playerQuad.Position.y += 0.1f;
		if (AF::Input::IsKeyPressed('S'))
			playerQuad.Position.y -= 0.1f;
		if (AF::Input::IsKeyPressed('A'))
			playerQuad.Position.x -= 0.1f;
		if (AF::Input::IsKeyPressed('D'))
			playerQuad.Position.x += 0.1f;

		AF::Renderer::Begin();
		
		for (int i = 0; i < quads.size(); i++)
		{
			AF::Renderer::DrawQuad(quads[i].Position, quads[i].Size, grassTexture);
		}

		AF::Renderer::DrawQuad(playerQuad.Position, playerQuad.Size, playerTexture);

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
