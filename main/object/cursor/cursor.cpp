#include "cursor.h"
#include "../plot.h"

namespace Plotter
{
	Cursor::CursorStyle::CursorStyle(Color color, Flags flags, Coords titleOffset) :
		color		{ color },
		flags		{ flags },
		titleOffset	{ titleOffset }
	{
	}

	Cursor::Cursor(Plot* layout, CursorStyle style, Title::TitleStyle tstyle) :
		Object	{ layout },
		style	{ style },
		lines	{ sf::Lines, 4 },
		title	{ layout, tstyle }
	{
		onStyleChanged();
	}

	void Cursor::setPosition(Coords coords)
	{
		lines[0].position = Coords(coords.x, 0);
		lines[1].position = Coords(coords.x, layout->style.frameSize.y);
		lines[2].position = Coords(layout->style.frameSize.x, coords.y);
		lines[3].position = Coords(0, coords.y);

		auto value = layout->toValues(coords);
		title.setString(toString(value.x) + "; " + toString(value.y));
		
		auto offset = coords + style.titleOffset;
		if (offset.x + title.size.x + 5 >= layout->style.frameSize.x)	offset.x = layout->style.frameSize.x - title.size.x - 5;
		if (offset.y + title.size.y + 5 >= layout->style.frameSize.y)	offset.y = layout->style.frameSize.y - title.size.y - 5;

		title.setPosition(offset);	
	}

	void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(lines, states);
		//target.draw(title, states);
	}

	void Cursor::onStyleChanged()
	{
		lines[0].color = style.color;
		lines[1].color = style.color;
		lines[2].color = style.color;
		lines[3].color = style.color;
	}

	void Cursor::recompute()
	{
	}
}