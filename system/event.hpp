#pragma once

namespace System
{
	class Event
	{
	public:

		enum EventType
		{
			Closed,
			MouseMoved,
			MouseButtonPressed,
			MouseButtonReleased
		} type;

	};
}