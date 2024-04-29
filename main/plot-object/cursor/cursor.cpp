#include "cursor.h"
#include "../../plot.h"

namespace Plotter
{
	Cursor::Cursor(Plot* layout, CursorStyle style) :
		PlotObject	{ layout },
		style		{ style },
		lines		{ PrimitiveType::Lines, 4 }
	{
	}

	void Cursor::recompute()
	{
		auto left = layout->start.x;
		auto top = layout->start.y; 
		auto right = layout->end.x;
		auto bottom = layout->end.y;

		lines[0] = Vertex(layout->toCoords(left, position.y), style.color);
		lines[1] = Vertex(layout->toCoords(right, position.y), style.color);
		lines[2] = Vertex(layout->toCoords(position.x, top), style.color);
		lines[3] = Vertex(layout->toCoords(position.x, bottom), style.color);
	}

	void Cursor::onStyleChanged()
	{
		for (auto i = 0; i < lines.getSize(); i++)
			lines[i].color = style.color;
	}
}