#pragma once
#include <string>
#include "vec2.hpp"

namespace System
{
	struct Text
	{
		Text();
		Text(Vec2 position);
		Text(std::string string);
		Text(std::string string, Vec2 position);

		std::string string		{ "" };
		Vec2		position	{ 0, 0 };
	};

	
}