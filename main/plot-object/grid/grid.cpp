#include "grid.h"
#include "../../plot.h"

namespace Plotter
{
	Grid::Grid(Plot* layout, GridStyle style) :
		PlotObject	{ layout },
		style		{ style },
		linesV		{ sf::PrimitiveType::Lines },
		linesH		{ sf::PrimitiveType::Lines }
	{
	}

	void Grid::recompute()
	{
		linesV.resize(2 * (style.countX + 1));
		linesH.resize(2 * (style.countY + 1));

		auto& valuesX = layout->title.valuesX;
		auto& valuesY = layout->title.valuesY;

		valuesX.resize(style.countX + 1);
		valuesY.resize(style.countY + 1);

		auto left = layout->vStart.x;
		auto top = layout->vEnd.y;
		auto right = layout->vEnd.x;
		auto bottom = layout->vStart.y;

		auto gScale = Vec2(
			(right - left) / style.countX,
			(top - bottom) / style.countY
		);

		for (auto x = 0; x <= style.countX; x++)
		{
			auto vx = left + x * gScale.x;

			linesV[2 * x] = Vertex(layout->toCoords(vx, top), style.color);
			linesV[2 * x + 1] = Vertex(layout->toCoords(vx, bottom), style.color);

			valuesX[x].value = toString(vx);
			valuesX[x].coords.x = vx;
		}

		for (auto y = 0; y <= style.countY; y++)
		{
			auto vy = bottom + y * gScale.y;

			linesH[2 * y] = Vertex(layout->toCoords(left, vy), style.color);
			linesH[2 * y + 1] = Vertex(layout->toCoords(right, vy), style.color);

			valuesY[y].value = toString(vy);
			valuesY[y].coords.y = vy;
		}
	}

	void Grid::onStyleChanged()
	{
		recompute();
	}
}