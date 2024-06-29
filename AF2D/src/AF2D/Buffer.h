#pragma once

namespace AF {

	class TextureBuffer
	{
	public:
		unsigned char* m_Data;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Components;
	};

	class Buffer
	{
	public:
		void* m_Data;
		unsigned int m_Size;
	};

}

