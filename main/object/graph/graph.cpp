#include "graph.h"
#include "../plot.h"

namespace Plotter
{
	Graph::GraphStyle::GraphStyle(Color color, Flags flags, uint8_t transparency) :
		color			{ color },
		flags			{ flags },
		transparency	{ transparency }
	{
	}

	Graph::Graph(Plot* layout, GraphStyle style) :
		Object	{ layout },
		style	{ style },
		line	{ sf::LineStrip },
		volume	{ sf::TriangleStrip }
	{
	}

	void Graph::graph(Func func, float start, float end)
	{
		points.clear();

		auto step = (end - start) / layout->style.pointCount;
		for (auto x = start; x <= end; x += step)
		{
			auto point = Values(x, func(x));
			points.push_back(point);

			if (point.y > max.y) max = point;
			if (point.y < min.y) min = point;	
		}

		function = func;
	}

	void Graph::graph(const vector<Values>& points)
	{
		for (auto& point : points)
		{
			if (point.y > max.y) max = point;
			if (point.y < min.y) min = point;
		}
		this->points = points;
		function = nullptr;
	}

	void Graph::rebuild()
	{
		if (function)
			graph(function, layout->start.x, layout->end.x);
	}

	void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		switch (style.flags)
		{
		case GraphStyle::SHOW_LINE:
			target.draw(line, states);
			break;
		case GraphStyle::SHOW_VOLUME:
			target.draw(volume, states);
			break;
		case GraphStyle::SHOW_ALL:
			target.draw(line, states);
			target.draw(volume, states);
			break;

		default:
			break;
		}
	}

	void Graph::onStyleChanged()
	{
	}

	void Graph::recompute()
	{
		line.clear();
		volume.clear();
		for (auto& point : points)
		{
			line.append(sf::Vertex(
				layout->toCoords(point),
				style.color
			));

			volume.append(sf::Vertex(
				layout->toCoords(point),
				Color(style.color.toInteger() + style.transparency)
			));

			volume.append(sf::Vertex(
				layout->toCoords(point.x, 0),
				Color(style.color.toInteger() + style.transparency)
			));
		}
	}
	
	

}
