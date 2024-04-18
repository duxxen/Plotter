#include "axis.h"
#include "plot.h"

namespace Plotter
{
	Axis::Axis(Plot* layout) :
		PlotObject	{ layout },
		style		{ ASTYLE_PRESETS[STYLE_DEFAULT] }
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

		auto& valuesX = layout->titles.valuesX;
		auto& valuesY = layout->titles.valuesY;
		auto indent = layout->titles.style.indent;

		if (style.centered)
		{
			lines.setPrimitiveType(sf::Lines);
			lines.resize(4);
			
			lines[0] = Vertex(layout->toCoords(centerX, top), style.color);
			lines[1] = Vertex(layout->toCoords(centerX, bottom), style.color);
			lines[2] = Vertex(layout->toCoords(left, centerY), style.color);
			lines[3] = Vertex(layout->toCoords(right, centerY), style.color);

			for (auto& value : valuesX)
				value.coords = layout->toCoords(value.coords.x, centerY);

			for (auto& value : valuesY)
				value.coords = layout->toCoords(centerX, value.coords.y);
		}
		else
		{
			lines.setPrimitiveType(sf::LineStrip);
			lines.resize(5);
			
			lines[0] = Vertex(layout->toCoords(left, top), style.color);
			lines[1] = Vertex(layout->toCoords(right, top), style.color);
			lines[2] = Vertex(layout->toCoords(right, bottom), style.color);
			lines[3] = Vertex(layout->toCoords(left, bottom), style.color);
			lines[4] = Vertex(layout->toCoords(left, top), style.color);

			for (auto& value : valuesX)
				value.coords = layout->toCoords(value.coords.x, bottom);

			for (auto& value : valuesY)
				value.coords = layout->toCoords(left, value.coords.y) - Vec2(indent + 3 * value.value.size(), 0); // xD
			
		}
	}

	void Axis::onStyleChanged()
	{
		recompute();
	}
}

