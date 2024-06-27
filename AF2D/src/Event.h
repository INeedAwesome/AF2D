#pragma once

namespace AF {
	struct Event
	{
		enum Type	
		{
			NONE, 
			CLOSED
		};
		
		Type type;
	};


}
