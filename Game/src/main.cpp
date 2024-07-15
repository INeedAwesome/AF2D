#include <AF2D.h>

#include <iostream>

struct GameState {
	int frames = 0;
	int selectedHand = 0;
	bool isHandDown = false;
	int timesHandDown = 0;

	AF::Texture2D chooseHand;
	AF::Texture2D handInAir;
	AF::Texture2D handDown;

	AF::Texture2D rockTexture;
	AF::Texture2D paperTexture;
	AF::Texture2D scissorsTexture;

	GameState()
	: chooseHand(), handInAir(), handDown(), rockTexture(), paperTexture(), scissorsTexture()
	{}

};

struct Quad {
	glm::vec3 Position;
	glm::vec2 Size;
};

void ResetGame(GameState& state, int& randomTextureIndex);

int Main()
{
	GameState gameState{};
	const int width = 1280;
	const int height = 720;
	const float aspectRatio = (float)width / (float)height;

	srand(time(NULL));

	AF::Window window(L"2D Game", width, height, AF::Window::CUSTOM);
	AF::Camera camera;

	AF::Renderer::Init();
	AF::Renderer::Resize(window.GetWidth(), window.GetHeight());
	
	AF::Input::RegisterRawInput();

	Quad screenQuad{};
	screenQuad.Size = { 1 * aspectRatio, 1 };
	
	gameState.chooseHand.Init("assets/Bild1.png");
	gameState.handInAir.Init("assets/up.png");
	gameState.handDown.Init("assets/down.png");

	gameState.rockTexture.Init("assets/rock.png");
	gameState.paperTexture.Init("assets/paper.png");
	gameState.scissorsTexture.Init("assets/scissors.png");

	//ResetGame(gameState);
	int currentTextureIndex = 0;
	int randomTextureIndex = 0;

	while (window.IsOpen())
	{
		while (window.PollEvent())
		{
			AF::Event::Type event = window.GetEvent(); 
			if (event == AF::Event::CLOSED)
				window.Close();
			if (event == AF::Event::RESIZED)
			{
				AF::Renderer::Resize(window.GetWidth(), window.GetHeight());
				screenQuad.Size.x = ((float)window.GetWidth() / (float)window.GetHeight());
			}
		}

		if (AF::Input::WasKeyPressed('1'))
			gameState.selectedHand = 1;
		else if (AF::Input::WasKeyPressed('2'))
			gameState.selectedHand = 2;
		else if (AF::Input::WasKeyPressed('3'))
			gameState.selectedHand = 3;
		else if (AF::Input::WasKeyPressed('R'))
		{
			ResetGame(gameState, randomTextureIndex);
			currentTextureIndex = 0;
		}

		if (gameState.selectedHand == 0)
			currentTextureIndex = 0;
		else 
		{
			gameState.frames++;
				if (gameState.isHandDown)
				currentTextureIndex = 1;
			else
				currentTextureIndex = 2;
			if (gameState.frames >= 30)
			{
				gameState.isHandDown = !gameState.isHandDown;
				gameState.frames = 0;
				gameState.timesHandDown++;
			}

			if (gameState.timesHandDown >= 6)
				currentTextureIndex = randomTextureIndex + 3;
		}

		AF::Renderer::Begin(camera);

		switch (currentTextureIndex)
		{
		case 0:
			AF::Renderer::DrawQuad(screenQuad.Position, screenQuad.Size, gameState.chooseHand);
			break;
		case 1:
			AF::Renderer::DrawQuad(screenQuad.Position, screenQuad.Size, gameState.handDown);
			break;
		case 2:
			AF::Renderer::DrawQuad(screenQuad.Position, screenQuad.Size, gameState.handInAir);
			break;
		case 3:
			AF::Renderer::DrawQuad(screenQuad.Position, screenQuad.Size, gameState.rockTexture);
			break;
		case 4:
			AF::Renderer::DrawQuad(screenQuad.Position, screenQuad.Size, gameState.paperTexture);
			break;
		case 5:
			AF::Renderer::DrawQuad(screenQuad.Position, screenQuad.Size, gameState.scissorsTexture);
			break;
		default:
			break;
		}


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

void ResetGame(GameState& state, int& randomTextureIndex)
{
	state.frames = 0;
	state.selectedHand = 0;
	state.isHandDown = false;
	state.timesHandDown = 0;

	int random = rand() % 3;
	if (random == 0)
		randomTextureIndex = 0;
	else if (random == 1)
		randomTextureIndex = 1;
	else if (random == 2)
		randomTextureIndex = 2;


}
