#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Axis;
class Locator;
class Grid;
class Plot;
class Window;

struct PlotterTuple
{
	Window* wptr;
	Plot*	pptr;
};

extern const float			DEFAULT_LOCATOR_MAJOR_LENGHT;
extern const float			DEFAULT_LOCATOR_MINOR_LENGHT;
extern const std::string	DEFAULT_FONTS_FOLDER;
extern const std::string	DEFAULT_FONT_NAME;
extern sf::Font				DEFAULT_FONT;
extern const sf::Color		DEFAULT_BACKGROUND_COLOR;