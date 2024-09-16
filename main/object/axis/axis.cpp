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
		lines	{ sf::Lines, 4 }
	{
	}

	void Axis::onStyleChanged(AxisStyle nstyle)
	{
		auto ostyle = style;
		style = nstyle;

		if (ostyle.centered != style.centered)
			recompute();
		else
		{
			lines[0].color = style.color;
			lines[1].color = style.color;
			lines[2].color = style.color;
			lines[3].color = style.color;
		}
	}

	void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(lines, states);
	}

	void Axis::init()
	{
		recompute();
	}

	void Axis::recompute()
	{
		auto zero = layout->toCoords(Values(0, 0));
		auto position = Coords(
			std::min(std::max(zero.x, 0.f), layout->frameSize.x),
			std::min(std::max(zero.y, 0.f), layout->frameSize.y)
		);
		intersection = style.centered ? position : Coords(0, 0);

		lines[0] = sf::Vertex(Coords(intersection.x, 0), style.color);
		lines[1] = sf::Vertex(Coords(intersection.x, layout->frameSize.y), style.color);
		lines[2] = sf::Vertex(Coords(0, intersection.y), style.color);
		lines[3] = sf::Vertex(Coords(layout->frameSize.x, intersection.y), style.color);
	}
}