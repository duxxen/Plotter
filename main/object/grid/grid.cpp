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
		linesH	{ sf::Lines },
		linesV	{ sf::Lines },
		example	{ layout, tstyle }
	{
		onStyleChanged();
	}

	void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(linesH, states);
		target.draw(linesV, states);

		//for (auto& title : titles)
			//target.draw(title, states);
	}

	void Grid::onStyleChanged()
	{
		auto size = sf::Vector2i(style.countX + 1, style.countY + 1);
		linesV.resize(2 * size.x);
		linesH.resize(2 * size.y);
		titles.resize(size.x + size.y, example);
		recompute();
	}

	void Grid::recompute()
	{
		auto step = Coords(
			layout->style.frameSize.x / style.countX,
			layout->style.frameSize.y / style.countY
		);

		auto titleOffset = Coords(
			0,								// { horizontal title } - variable
			-example.style.charSize / 2		// { vertical title }	- const
		);
		auto titlePosition = Coords(
			-example.style.charSize / 2,	// { vertical title }	- variable
			layout->style.frameSize.y		// { horizontal title } - const
		);
		if (layout->axis.style.centered)
			titlePosition = layout->axis.intersection + Coords(-5, 0);



		for (auto i = 0; i <= style.countX; i++)
		{
			// Vertical Line
			auto posx = i * step.x;
			linesV[2 * i] = sf::Vertex(Coords(posx, 0), style.color);
			linesV[2 * i + 1] = sf::Vertex(Coords(posx, layout->style.frameSize.y), style.color);

			// Horizontal Title
			titles[i].setString(toString(layout->toValues(posx, 0).x));

			titleOffset.x = -titles[i].size.x / 2.f;
			posx = std::min(std::max(posx + titleOffset.x, 0.f), layout->style.frameSize.x + 2.3f * titleOffset.x); // xD

			titles[i].setPosition(posx, titlePosition.y);
		}
		
		for (auto i = 0; i <= style.countY; i++)
		{
			// Horizontal Line
			auto posy = i * step.y;
			linesH[2 * i] = sf::Vertex(Coords(0, posy), style.color);
			linesH[2 * i + 1] = sf::Vertex(Coords(layout->style.frameSize.x, posy), style.color);

			// Vertical Title
			auto index = style.countX + i + 1;
			titles[index].setString(toString(layout->toValues(0, posy).y));

			auto posx = titlePosition.x - titles[index].size.x;
			posy = std::min(std::max(posy + titleOffset.y, 0.f), layout->style.frameSize.y + 2.6f * titleOffset.y); // xDDD

			titles[index].setPosition(posx, posy);
		}
	}
}