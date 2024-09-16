#include "title.h"
#include "../plot.h"

namespace Plotter
{
	sf::Font Title::font	{ };
	bool Title::fontLoaded	{ false };

	Title::TitleStyle::TitleStyle(Color color, uint8_t charSize, string fontPath) :
		color		{ color },
		charSize	{ charSize },
		fontPath	{ fontPath }
	{
	}

	Title::Title(Plot* layout, TitleStyle style) :
		Object	{ layout }
	{
	}

	void Title::setString(string string)
	{
		text.setString(string);
		size.x = text.getLocalBounds().width;
		size.y = text.getLocalBounds().height;
	}

	void Title::onStyleChanged(TitleStyle nstyle)
	{
		auto ostyle = style;
		style = nstyle;

		if (style.fontPath != nstyle.fontPath)
		{
			font.loadFromFile(style.fontPath);
			text.setFont(font);
		}

		text.setFillColor(style.color);
		text.setCharacterSize(style.charSize);
	}

	void Title::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(text, states);
	}

	void Title::init()
	{
		if (!fontLoaded)
		{
			font.loadFromFile(style.fontPath);
			fontLoaded = true;
		}
		text.setFont(font);
		text.setFillColor(style.color);
		text.setCharacterSize(style.charSize);
	}

	void Title::recompute()
	{
	}
}