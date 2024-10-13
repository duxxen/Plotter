#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Axis;
class Grid;
class Plot;
class Window;

struct PlotterTuple
{
	Window* wptr;
	Plot*	pptr;
};

//class Layout
//{
//public:
//	Layout(Layout* layout = nullptr) : layout(layout) {}
//	Layout* toLayout() { return layout; }
//private:
//	Layout* layout;
//};

static inline const float		DEFAULT_LOCATOR_MAJOR_LENGHT	{ 5.f };
static inline const float		DEFAULT_LOCATOR_MINOR_LENGHT	{ 3.f };
static inline const std::string	DEFAULT_FONTS_FOLDER			{ "C:/Windows/Fonts/" };
static inline const std::string DEFAULT_FONT_NAME				{ "arial.ttf" };
static inline const sf::Color	DEFAULT_BACKGROUND_COLOR		{ 255, 255, 255 };