#pragma once

namespace AF {
	struct Event
	{
		enum Type	
		{
			NONE, 
			CLOSED,
			RESIZED,
			MOUSE_MOVE
		};
		
		Type type;
	};


}
