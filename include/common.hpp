#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "system/plot-object.hpp"

class Label;
class Locator;
class Axis;
class Grid;
class Plot;
class Window;
class Plotter;

struct PlotterTuple
{
	Window* wptr;
	Plot*	pptr;
};

