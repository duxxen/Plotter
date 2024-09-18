#include "axis.h"
#include "../plot.h"

namespace Plotter
{
	Axis::AxisStyle::AxisStyle(Color color, bool centered, sf::String nameX, sf::String nameY) :
		color		{ color },
		centered	{ centered },
		nameX		{ nameX },
		nameY		{ nameY }
	{
	}

	Axis::Axis(Plot* layout, AxisStyle style, Title::TitleStyle tstyle) :
		Object	{ layout },
		lines	{ sf::Lines, 4 },
		style	{ style },
		nameX	{ layout, tstyle },
		nameY	{ layout, tstyle}
	{
	}

	void Axis::onStyleChanged(AxisStyle nstyle)
	{
		auto ostyle = style;
		style = nstyle;

		nameX.setString(nstyle.nameX);
		nameY.setString(nstyle.nameY);

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
		nameX.init();
		nameY.init();
		nameY.setRotation(-90);
		nameX.setString(style.nameX);
		nameY.setString(style.nameY);

		recompute();
	}

	void Axis::recompute()
	{
		intersection = layout->rangeCoords(layout->toCoords(0, 0));
		auto titlePosition = Coords(
			-DEFAULT_AXIS_NAME_INDENT - nameY.size.y,
			layout->frameSize.y + DEFAULT_TEXT_INDENT
		);

		if (!style.centered)
		{
			intersection = Coords(0, layout->frameSize.y);
			titlePosition.x -= DEFAULT_FRAME_INDENT_LEFT;
			titlePosition.y += 2.f * DEFAULT_TEXT_INDENT;
		}

		lines[0] = sf::Vertex(Coords(intersection.x, 0), style.color);
		lines[1] = sf::Vertex(Coords(intersection.x, layout->frameSize.y), style.color);
		lines[2] = sf::Vertex(Coords(0, intersection.y), style.color);
		lines[3] = sf::Vertex(Coords(layout->frameSize.x, intersection.y), style.color);

		nameX.setPosition(layout->frameSize.x / 2.f - nameX.size.x / 2.f, titlePosition.y);
		nameY.setPosition(titlePosition.x, layout->frameSize.y / 2.f + nameY.size.x / 2.f);
	}
}