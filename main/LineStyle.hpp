#pragma once
#include "Common.hpp"

namespace Plotter
{
	struct LineProperties
	{
		// Line color
		uint8_t		lColorR		{ 255 };
		uint8_t		lColorG		{ 0 };
		uint8_t		lColorB		{ 0 };
		uint8_t		lColorA		{ 255 };

		// Volume color
		uint8_t		vColorR		{ 255 };
		uint8_t		vColorG		{ 0 };
		uint8_t		vColorB		{ 0 };
		uint8_t		vColorA		{ DEFAULT_VOL_TRANSPARENCY };

		LineProperties() {}
		LineProperties(uint8_t r, uint8_t g, uint8_t b, uint8_t va) :
			lColorR(r), lColorG(g), lColorB(b),
			vColorR(r), vColorG(g), vColorB(b), vColorA(va)
		{
		}

	};
}