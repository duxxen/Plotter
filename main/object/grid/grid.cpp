#include "grid.h"
#include "../plot.h"

namespace Plotter
{
	Grid::GridStyle::GridStyle(size_t countX, size_t countY, Color color) :
		countX	{ countX },
		countY	{ countY },
		color	{ color }
	{
	}

	Grid::Grid(Plot* layout, GridStyle style, Title::TitleStyle tstyle) :
		Object	{ layout },
		style	{ style },
		example	{ layout, tstyle },
		linesH	{ sf::Lines },
		linesV	{ sf::Lines },
		titles	{ style.countX + style.countY + 2, example }
	{
	}

	void Grid::onStyleChanged(GridStyle nstyle)
	{
		auto ostyle = style;
		style = nstyle;

		if (ostyle.countX != style.countX || ostyle.countY != style.countY)
		{
			auto size = sf::Vector2i(style.countX + 1, style.countY + 1);
			linesV.resize(2 * size.x);
			linesH.resize(2 * size.y);
			titles.resize(size.x + size.y, example);
			recompute();
		}
		else
		{
			for (auto i = 0; i < linesH.getVertexCount(); i++)
				linesH[i].color = style.color;
		}
	}

	void Grid::onStyleChanged(Title::TitleStyle nstyle)
	{
		example.onStyleChanged(nstyle);
		for (auto& title : titles)
			title.onStyleChanged(nstyle);
	}

	void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(linesH, states);
		target.draw(linesV, states);

		//for (auto& title : titles)
			//target.draw(title, states);
	}

	void Grid::init()
	{
		auto size = sf::Vector2i(style.countX + 1, style.countY + 1);
		linesV.resize(2 * size.x);
		linesH.resize(2 * size.y);

		titles.resize(size.x + size.y, example);
		for (auto& title : titles)
			title.init();

		recompute();
	}

	void Grid::recompute()
	{
		auto step = Coords(
			layout->frameSize.x / style.countX,
			layout->frameSize.y / style.countY
		);
		auto frameIndent = Coords(
			DEFAULT_TEXT_INDENT,
			DEFAULT_TEXT_INDENT
		);
		auto titleOffset = Coords(
			0,								// { horizontal title } - variable
			-example.style.charSize / 2.f	// { vertical title }	- const
		);
		auto titlePosition = Coords(
			-example.style.charSize / 2.f,	// { horizontal title } - variable
			layout->frameSize.y				// { vertical title }	- const
		);

		if (layout->axis.style.centered)
			titlePosition = layout->axis.intersection + Coords(-DEFAULT_TEXT_INDENT, 0);
		
		for (auto x = 0; x <= style.countX; x++)
		{
			auto posx = x * step.x;

			// Lines Vertical
			linesV[2 * x] = sf::Vertex(Coords(posx, 0.f), style.color);
			linesV[2 * x + 1] = sf::Vertex(Coords(posx, layout->frameSize.y), style.color);

			// Titles Horizontal
			titles[x].setString(toString(layout->toValues(posx, 0.f).x));

			titleOffset.x = -titles[x].size.x / 2.f;
			posx = std::max(std::min(posx + titleOffset.x, layout->frameSize.x - titles[x].size.x - frameIndent.x), frameIndent.x);

			titles[x].setPosition(posx, titlePosition.y);
		}

		for (auto y = 0; y <= style.countY; y++)
		{
			auto posy = y * step.y;

			// Lines Horizontal
			linesH[2 * y] = sf::Vertex(Coords(0.f, posy), style.color);
			linesH[2 * y + 1] = sf::Vertex(Coords(layout->frameSize.x, posy), style.color);

			auto index = style.countX + y + 1;
			// Titles Vertical
			titles[index].setString(toString(layout->toValues(0.f, posy).y));

			auto posx = titlePosition.x - titles[index].size.x;
			posy = std::max(std::min(posy + titleOffset.y, layout->frameSize.y - titles[index].size.y - frameIndent.y), frameIndent.y);

			titles[index].setPosition(posx, posy);
		}
	}
}