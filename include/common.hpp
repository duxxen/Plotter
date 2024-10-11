#pragma once
#include <SFML/Graphics.hpp>

class Axis;
class Grid;
class Plot;
class WindowFrame;
class Plotter;

typedef std::shared_ptr<Plot>			PlotPointer;
typedef std::shared_ptr<WindowFrame>	WindowFramePointer;
typedef std::tuple<WindowFrame&, Plot&>	PlotterTuple;