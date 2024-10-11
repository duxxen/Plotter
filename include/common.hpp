#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

class Axis;
class Grid;
class Plot;
class WindowFrame;
class Plotter;

typedef std::shared_ptr<Plot>			PlotPointer;
typedef std::shared_ptr<WindowFrame>	WindowFramePointer;
typedef std::tuple<WindowFrame&, Plot&>	PlotterTuple;

static inline std::string toString(float value, std::streamsize precision = 3)
{
	std::stringstream ss;
	std::string str;
	ss.precision(precision);
	ss << value;
	ss >> str;

	return str;
}