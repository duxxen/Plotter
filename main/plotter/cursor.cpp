#include "cursor.h"
#include "plot.h"

namespace Plotter
{

	Cursor::Cursor(Plot* layout) :
		PlotObject	{ layout },
		style		{ CSTYLE_PRESETS[STYLE_DEFAULT] },
		lines		{ sf::Lines, 4 }
	{
	}

	void Cursor::recompute()
	{
		auto left = layout->vStart.x;
		auto right = layout->vEnd.x;
		auto bottom = layout->vStart.y;
		auto top = layout->vEnd.y;

		auto mouse = layout->toValues(layout->mouseCoords);
		auto& values = layout->titles.valuesC;

		lines[0] = Vertex(layout->toCoords(mouse.x, top));
		lines[1] = Vertex(layout->toCoords(mouse.x, bottom));
		lines[2] = Vertex(layout->toCoords(left, mouse.y));
		lines[3] = Vertex(layout->toCoords(right, mouse.y));

		values.value = toString(mouse.x) + ", " + toString(mouse.y);
		values.coords = mouse;
	}

	void Cursor::onStyleChanged()
	{
		for (auto i = 0; i < 4; i++)
			lines[i].color = style.color;
	}

}