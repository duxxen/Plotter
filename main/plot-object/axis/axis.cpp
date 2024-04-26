#include "axis.h"
#include "../../plot.h"

namespace Plotter
{
	Axis::Axis(Plot* layout, AxisStyle style) :
		PlotObject	{ layout },
		style		{ style }
	{
	}

	void Axis::recompute()
	{
		auto left = layout->vStart.x;
		auto right = layout->vEnd.x;
		auto top = layout->vEnd.y;
		auto bottom = layout->vStart.y;

		auto centerX = std::min(std::max(left, 0.f), right);
		auto centerY = std::min(std::max(bottom, 0.f), top);

		auto& valuesX = layout->title.valuesX;
		auto& valuesY = layout->title.valuesY;
		auto indent = layout->title.style.indent;

		if (style.centered)
		{
			aLines.setPrimitiveType(sf::Lines);
			aLines.resize(4);

			aLines[0] = Vertex(layout->toCoords(centerX, top), style.color);
			aLines[1] = Vertex(layout->toCoords(centerX, bottom), style.color);
			aLines[2] = Vertex(layout->toCoords(left, centerY), style.color);
			aLines[3] = Vertex(layout->toCoords(right, centerY), style.color);

			for (auto& value : valuesX)
				value.coords = layout->toCoords(value.coords.x, centerY);

			for (auto& value : valuesY)
				value.coords = layout->toCoords(centerX, value.coords.y);
		}
		else
		{
			aLines.setPrimitiveType(sf::LineStrip);
			aLines.resize(5);

			aLines[0] = Vertex(layout->toCoords(left, top), style.color);
			aLines[1] = Vertex(layout->toCoords(right, top), style.color);
			aLines[2] = Vertex(layout->toCoords(right, bottom), style.color);
			aLines[3] = Vertex(layout->toCoords(left, bottom), style.color);
			aLines[4] = Vertex(layout->toCoords(left, top), style.color);

			for (auto& value : valuesX)
				value.coords = layout->toCoords(value.coords.x, bottom);

			for (auto& value : valuesY)
				value.coords = layout->toCoords(left, value.coords.y) - Vec2(indent + 3.5 * value.value.size(), 0); // xD
			
		}
	}

	void Axis::onStyleChanged()
	{
		recompute();
	}
}

