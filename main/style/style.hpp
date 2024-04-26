#pragma once
#include "../common.hpp"

#define STYLE_DEFAULT	0

namespace Plotter
{

	struct Style
	{
		// Style Properties
		sf::Color color;

		Style(sf::Color color) :
			color{ color }
		{
		}
	};

}