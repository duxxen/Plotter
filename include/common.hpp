#pragma once
#include "system/label.h"
#include "system/singleton.h"
#include "system/plot-object.hpp"

class Label;
class Locator;
class Axis;
class Plot;
class Window;
class Plotter;

struct PlotterTuple
{
	Window*					wptr;
	std::map<size_t, Plot*>	pptrs;

	PlotterTuple(Window* wptr, Plot* pptr) :
		wptr	(wptr),
		pptrs	({ std::make_pair(1, pptr) })
	{
	}
};

