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
		auto left = layout->start.x;
		auto right = layout->end.x;
		auto top = layout->start.y;
		auto bottom = layout->end.y;

		auto centerX = std::min(std::max(left, 0.f), right);
		auto centerY = std::min(std::max(bottom, 0.f), top);

		auto& valuesX = layout->titles.valuesX;
		auto& valuesY = layout->titles.valuesY;
		auto indent = layout->titles.style.indent;

		if (style.centered)
		{
			lines.setType(PrimitiveType::Lines);
			lines.resize(4);

			lines[0] = Vertex(layout->toCoords(centerX, top), style.color);
			lines[1] = Vertex(layout->toCoords(centerX, bottom), style.color);
			lines[2] = Vertex(layout->toCoords(left, centerY), style.color);
			lines[3] = Vertex(layout->toCoords(right, centerY), style.color);

			for (auto& value : valuesX)
				value.position = layout->toCoords(value.position.x, centerY);

			for (auto& value : valuesY)
				value.position = layout->toCoords(centerX, value.position.y);
		}
		else
		{
			lines.setType(PrimitiveType::LineStrip);
			lines.resize(5);
			
			lines[0] = Vertex(layout->toCoords(left, top), style.color);
			lines[1] = Vertex(layout->toCoords(right, top), style.color);
			lines[2] = Vertex(layout->toCoords(right, bottom), style.color);
			lines[3] = Vertex(layout->toCoords(left, bottom), style.color);
			lines[4] = Vertex(layout->toCoords(left, top), style.color);

			for (auto& value : valuesX)
				value.position = layout->toCoords(value.position.x, bottom);

			for (auto& value : valuesY)
				value.position = layout->toCoords(left, value.position.y) - Vec2(indent + 3.5 * value.string.size(), 0); // xD

		}
	}

	void Axis::onStyleChanged()
	{
		recompute();
	}
}