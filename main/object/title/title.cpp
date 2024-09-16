#include "title.h"
#include "../plot.h"

namespace Plotter
{
	Title::TitleStyle::TitleStyle(Color color, uint8_t charSize, string fontPath) :
		color		{ color },
		charSize	{ charSize },
		fontPath	{ fontPath }
	{
	}

	Title::Title(Plot* layout, TitleStyle style) :
		Object	{ layout },
		style	{ style }
	{
		onStyleChanged();
	}

	void Title::setString(string string)
	{
		text.setString(string);
		size.x = text.getLocalBounds().width;
		size.y = text.getLocalBounds().height;
	}

	void Title::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(text, states);
	}

	void Title::onStyleChanged()
	{
		font.loadFromFile(style.fontPath);
		text.setFont(font);
		text.setFillColor(style.color);
		text.setCharacterSize(style.charSize);
	}

	void Title::recompute()
	{
	}
}