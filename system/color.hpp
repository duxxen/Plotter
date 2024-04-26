#pragma once
#include <stdint.h>

namespace System
{
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color();
		Color(uint32_t integer);
		Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255U);
	};

	Color::Color() :
		r	{ 255U },
		g	{ 255U },
		b	{ 255U },
		a	{ 255U }
	{
	}

	Color::Color(uint32_t integer) :
		r	{ (integer >> 24) & 255 },
		g	{ (integer >> 16) & 255 },
		b	{ (integer >> 8)  & 255 },
		a	{ (integer >> 0)  & 255 }
	{
	}

	Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
		r	{ red },
		g	{ green },
		b	{ blue },
		a	{ alpha }
	{
	}
}