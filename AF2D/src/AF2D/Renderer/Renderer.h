#pragma once

namespace AF {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin();
		static void End();

		static void DrawQuad();

	private:

	};

}
