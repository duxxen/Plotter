#pragma once

namespace System
{
	struct Mouse
	{
		enum Button
		{
			LEFT,
			RIGHT,
			MIDDLE
		};

		float	x, y;
		Button	button;
		bool	pressed;
	};
}