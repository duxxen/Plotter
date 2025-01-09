#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cassert>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>

#include "mathex.hpp"

/*
*  #define DEFAULT_WIN_WIDTH  800U
#define DEFAULT_WIN_HEIGHT 600U
#define DEFAULT_GRAPH_OFFSET { 30.0f, 20.0f }
#define DEFAULT_GRAPH_MARGIN { 20.0f, 30.0f }
#define DEFAULT_LEGEND_MARGIN { 10.0f, 10.0f }
#define DEFAULT_GRID_COUNT { 10, 10 }

#define DEFAULT_GRID_COLOR { 0x }

#define DEFAULT_VALUES_MARGIN_PERCENTAGE 0.1f
* 
*/

static const uint16_t DEFAULT_WIN_WIDTH { 800U };
static const uint16_t DEFAULT_WIN_HEIGHT{ 600U };

static const sf::Vector2f DEFAULT_GRAPH_OFFSET { 30.0f, 20.0f };
static const sf::Vector2f DEFAULT_GRAPH_MARGIN { 20.0f, 30.0f };
static const sf::Vector2f DEFAULT_LEGEND_MARGIN{ 10.0f, 10.0f };

static const sf::Vector2u DEFAULT_GRID_COUNT { 10U, 10U };

static const float DEFAULT_VALUES_MARGIN_PERCENTAGE { 0.1f };

static const uint8_t DEFAULT_FONT_SIZE { 12U };
static const std::string DEFAULT_FONT_PATH { "../assets/arial.ttf" };

static const std::unordered_map<std::string, sf::Color> DEFAULT_COLORS = {
	{ "black",     sf::Color(0x000000ff) },
	{ "white",     sf::Color(0xffffffff) },
	{ "red",       sf::Color(0xff0000ff) },
	{ "green",     sf::Color(0x00ff00ff) },
	{ "blue",      sf::Color(0x0000ffff) },
	{ "cyan",      sf::Color(0x00ffffff) },
	{ "magenta",   sf::Color(0xff00ffff) },
	{ "yellow",    sf::Color(0xffff00ff) },
	{ "navy",      sf::Color(0x000080ff) },
	{ "fuchsia",   sf::Color(0xff00ffff) },
	{ "coral",     sf::Color(0xff7f50ff) },
	{ "tomato",    sf::Color(0xff6347ff) },
	{ "crimson",   sf::Color(0xdc143cff) },
	{ "salmon",    sf::Color(0xfa8072ff) },
	{ "olive",     sf::Color(0x808000ff) },
	{ "dimgray",   sf::Color(0x696969ff) },
	{ "silver",    sf::Color(0xc0c0c0ff) },
	{ "slategray", sf::Color(0x708090ff) },
	{ "wheat",     sf::Color(0xf5deb3ff) },
	{ "seagreen",  sf::Color(0x2e8b57ff) },
	{ "aliceblue", sf::Color(0xf0f8ffff) },
	{ "seashell",  sf::Color(0xfff5eeff) },
	{ "khaki",     sf::Color(0xf0e68cff) }
};

static const std::vector<std::string> DEFAULT_GRAPH_COLORS_STR = {
	"salmon", "fuchsia", "olive", "navy", "crimson", "seagreen", "coral", "wheat", "cyan", "tomato", "red", "green", "blue"
};