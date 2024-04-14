#pragma once
#include "Common.hpp"
#include "assets/AssetManager.hpp"

namespace Plotter
{
	struct PlotProperties
	{
		// Plot area sizes
		uint32_t	width		{ DEFAULT_WIN_WIDTH  };		
		uint32_t	height		{ DEFAULT_WIN_HEIGHT };
		uint32_t	indent		{ DEFAULT_WIN_INDENT };

		// Grid color
		uint8_t		gColorR		{ 64 };
		uint8_t		gColorG		{ 64 };
		uint8_t		gColorB		{ 64 };
		uint8_t		gColorA		{ 255 };

		// Axis color
		uint8_t		aColorR		{ 255 };
		uint8_t		aColorG		{ 255 };
		uint8_t		aColorB		{ 255 };
		uint8_t		aColorA		{ 255 };
			
		// Frame color
		uint8_t		fColorR		{ 255 };
		uint8_t		fColorG		{ 255 };
		uint8_t		fColorB		{ 255 };
		uint8_t		fColorA		{ 255 };

		// Background color
		uint8_t		bColorR		{ 0 };
		uint8_t		bColorG		{ 0 };
		uint8_t		bColorB		{ 0 };
		uint8_t		bColorA		{ 255 };

		// Grid count
		uint32_t	gCountX		{ 10 };
		uint32_t	gCountY		{ 10 };

		// Text color
		uint8_t		tColorR		{ 255 };
		uint8_t		tColorG		{ 255 };
		uint8_t		tColorB		{ 255 };
		uint8_t		tColorA		{ 255 };

		// Text properties
		std::string	fontPath	{ "src/assets/arial.ttf" };
		uint32_t	textIndent	{ DEFAULT_TEXT_INDENT };
		uint32_t	charSize	{ 10 };
		sf::Font	font;

		bool		showGrid	{ true };
		bool		showAxis	{ true };
		bool		showVolume	{ true };
		bool		centerAxis	{ true };

		uint32_t	pointCount	{ DEFAULT_POINT_COUNT };
		
		

		PlotProperties() { font = AssetManager::getFont(fontPath); }
	};
}