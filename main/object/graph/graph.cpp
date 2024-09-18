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
		max = min = Values(start, func(start));

		auto temp = start;
		start = std::min(start, end);
		end = std::max(temp, end);


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

		if (style.flags & GraphStyle::SHOW_LINE)
			target.draw(line, states);
		
		if (style.flags & GraphStyle::SHOW_VOLUME)
			target.draw(volume, states);
	}

	void Graph::onStyleChanged(GraphStyle nstyle)
	{
		style = nstyle;

		for (auto i = 0; i < line.getVertexCount(); i++)
			line[i].color = style.color;

		for (auto i = 0; i < volume.getVertexCount(); i++)
			volume[i].color = Color(style.color.toInteger() + style.transparency);
	}

	void Graph::init()
	{
	}

	void Graph::recompute()
	{
		line.clear();
		volume.clear();
		for (auto& point : points)
		{
			auto coords = layout->rangeCoords(layout->toCoords(point));
			//auto coords = (layout->toCoords(point));
			
			line.append(sf::Vertex(
				coords,
				style.color
			));

			volume.append(sf::Vertex(
				coords,
				Color(style.color.toInteger() + style.transparency)
			));

			volume.append(sf::Vertex(
				layout->toCoords(point.x, 0),
				Color(style.color.toInteger() + style.transparency)
			));
			
		}
	}
	
	

}
