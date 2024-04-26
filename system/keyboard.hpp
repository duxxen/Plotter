#pragma once

namespace System
{
	struct Keyboard
	{
		enum Key
		{
			UNKNOWN,
			LEFT,
			RIGHT,
			UP,
			DOWN,

			LSHIFT,
			RSHIFT,
			LCTRL,
			RCTRL,
			LALT,
			RALT,

			SPACE,
			ESCAPE,
			ENTER,
			TAB,

			NUM_0,
			NUM_1,
			NUM_2,
			NUM_3,
			NUM_4,
			NUM_5,
			NUM_6,
			NUM_7,
			NUM_8,
			NUM_9,

			L,
			R
		};

		Key		code;
		bool	shift;
		bool	control;
		bool	alt;
		bool	pressed;
	};
}