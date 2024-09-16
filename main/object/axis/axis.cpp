#include "axis.h"
#include "../plot.h"

namespace Plotter
{
	Axis::AxisStyle::AxisStyle(Color color, bool centered) :
		color		{ color },
		centered	{ centered }
	{
	}

	Axis::Axis(Plot* layout, AxisStyle style) :
		Object	{ layout },
		style	{ style },
		lines	{ sf::Lines, 4 }
	{
		onStyleChanged();
		recompute();
	}

	void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(lines, states);
	}

	void Axis::onStyleChanged()
	{
		recompute();
	}

	void Axis::recompute()
	{
		auto zero = layout->toCoords(Values(0, 0));
		auto center = Coords(
			std::min(std::max(zero.x, 0.f), layout->style.frameSize.x),
			std::min(std::max(zero.y, 0.f), layout->style.frameSize.y)
		);
		intersection = style.centered ? center : Coords(0, 0);

		lines[0] = sf::Vertex(Coords(intersection.x, 0), style.color);
		lines[1] = sf::Vertex(Coords(intersection.x, layout->style.frameSize.y), style.color);
		lines[2] = sf::Vertex(Coords(0, intersection.y), style.color);
		lines[3] = sf::Vertex(Coords(layout->style.frameSize.x, intersection.y), style.color);
	}
}