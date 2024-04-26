#include "graph.h"
#include "../../plot.h"

namespace Plotter
{
	Graph::Graph(Plot* layout) :
		PlotObject	{ layout },
		func		{ nullptr },
		style		{ LSTYLE_PRESETS[STYLE_DEFAULT] },
		gLines		{ sf::LineStrip },
		vTriangles	{ sf::TriangleStrip }
	{
	}

	Graph::Graph(Plot* layout, LineStyle style) :
		PlotObject	{ layout },
		func		{ nullptr },
		style		{ style },
		gLines		{ sf::LineStrip },
		vTriangles	{ sf::TriangleStrip }
	{
	}

	void Graph::graph(Func func, float from, float to)
	{
		points.clear();

		auto step = (to - from) / layout->style.pointCount;
		this->func = func;

		min.x = std::min(from, to);
		max.x = std::max(from, to);
		min.y = max.y = func(from);

		for (auto i = 0; i < layout->style.pointCount; i++)
		{
			auto x = from + i * step;
			auto y = this->func(x);
			min.y = std::min(min.y, y);
			max.y = std::max(max.y, y);

			points.push_back({ x, y });
		}
	}

	void Graph::graph(vector<Vec2> points)
	{
		this->points = points;
		for (auto p : points)
		{
			min.x = std::min(p.x, min.x);
			max.x = std::max(p.x, max.x);
			min.y = std::min(p.y, min.y);
			max.y = std::max(p.y, max.y);
		}

		this->func = [&](float x)
			{
				x = std::min(std::max(x, min.x), max.x);
				auto stepx = (max.x - min.x) / (this->points.size() - 1);
				auto i = size_t((x - min.x) / stepx);

				return this->points[i].y;
			};
		
	}

	void Graph::recompute()
	{
		gLines.resize(points.size());
		vTriangles.resize(points.size());

		Vec2 zero = layout->toCoordsRanged(0, 0);

		auto lColor = style.color;
		auto vColor = style.color;
		vColor.a	= style.vAlpha;

		for (auto i = 0; i < points.size(); i++)
		{
			auto coords = layout->toCoordsRanged(points[i]);

			gLines[i] = sf::Vertex(coords, lColor);
			if (i % 2 == 0 && i < points.size() - 1)
			{
				vTriangles[i] = sf::Vertex(coords, vColor);
				vTriangles[i + 1] = sf::Vertex(Vec2(coords.x, zero.y), vColor);
			}
		}
	}

	void Graph::onStyleChanged()
	{
		auto lColor = style.color;
		auto vColor = style.color;
		vColor.a	= style.vAlpha;

		for (int i = 0; i < gLines.getVertexCount(); i++)
			gLines[i].color = lColor;
		for (int i = 0; i < vTriangles.getVertexCount(); i++)
			vTriangles[i].color = vColor;
	}
}