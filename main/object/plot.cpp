#include "plot.h"

namespace Plotter
{
	//const Plot::PlotStyle Plot::DEFAULT_PLOT_STYLE;

	Plot::PlotStyle::PlotStyle(
		string windowName, 
		Coords windowSize, 
		Color backgroundColor, 
		Coords frameSize, 
		Coords framePosition, 
		Color frameColor, 
		uint32_t pointCount) 
		:
		windowName(windowName),
		windowSize(windowSize),
		backgroundColor(backgroundColor),
		frameSize(frameSize),
		framePosition(framePosition),
		frameColor(frameColor),
		pointCount(pointCount)
	{
	}

	Plot::Plot(
		PlotStyle pstyle, 
		Axis::AxisStyle astyle,
		Grid::GridStyle gstyle,
		Graph::GraphStyle lstyle, 
		Cursor::CursorStyle cstyle,
		Title::TitleStyle tstyle)
		:
		Object	{ nullptr },
		axis	{ this, astyle },
		grid	{ this, gstyle, tstyle },
		graph	{ this, lstyle },
		cursor	{ this, cstyle, tstyle }
	{
		init();
	}

	void Plot::init(
		PlotStyle pstyle, 
		Axis::AxisStyle astyle,
		Grid::GridStyle gstyle,
		Graph::GraphStyle lstyle,
		Cursor::CursorStyle cstyle,
		Title::TitleStyle tstyle)
	{
		setStyle(pstyle);
		setStyle(astyle);
		setStyle(gstyle);
		setStyle(lstyle);
		setStyle(cstyle);
		setStyle(tstyle);
	}

	void Plot::setPointCount(size_t pointCount)
	{
		style.pointCount = pointCount;
		plot(graph.function, start.x, end.x);
	}

	void Plot::setStyle(PlotStyle style)
	{
		this->style = style;
		onStyleChanged();
	}

	void Plot::setStyle(Axis::AxisStyle style)
	{
		axis.style = style;
		

		if (style.centered)
		{
			this->style.framePosition.x = DEFAULT_WIN_INDENT;
			this->style.frameSize.x = DEFAULT_WIN_WIDTH - 2 * DEFAULT_WIN_INDENT;
		}
		else
		{
			this->style.framePosition.x = DEFAULT_WIN_INDENT + DEFAULT_FRAME_INDENT_LEFT;
			this->style.frameSize.x = DEFAULT_WIN_WIDTH - 2 * DEFAULT_WIN_INDENT - DEFAULT_FRAME_INDENT_LEFT;
		}
		recompute();

		axis.onStyleChanged();
		grid.recompute();
		graph.recompute();
	}

	void Plot::setStyle(Grid::GridStyle style)
	{
		grid.style = style;
		grid.onStyleChanged();
	}

	void Plot::setStyle(Graph::GraphStyle style)
	{
		graph.style = style;
		graph.onStyleChanged();
	}

	void Plot::setStyle(Cursor::CursorStyle style)
	{
		cursor.style = style;
		cursor.onStyleChanged();
	}

	void Plot::setStyle(Title::TitleStyle style)
	{
		cursor.title.style = style;
		cursor.title.onStyleChanged();

		grid.example.style = style;
		for (auto& title : grid.titles)
		{
			title.style = style;
			title.onStyleChanged();
		}

		grid.recompute();
	}

	bool Plot::processEvents()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				cursor.setPosition(rangeCoords(event.mouseMove.x, event.mouseMove.y));

			default:
				break;
			}
		}

		return window.isOpen();
	}

	void Plot::update()
	{
	}

	void Plot::render()
	{
		window.clear(style.backgroundColor);
		window.draw(*this);
		window.display();
	}

	void Plot::initWindow()
	{
		window.create(sf::VideoMode(style.windowSize.x, style.windowSize.y), style.windowName, sf::Style::Close);
		window.setMouseCursorVisible(false);
	}

	void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(grid, states);
		target.draw(graph, states);
		target.draw(axis, states);
		target.draw(cursor, states);
		target.draw(frameShape, states);

		for (auto& title : grid.titles)
			target.draw(title, states);
		target.draw(cursor.title, states);
	}

	void Plot::plot(Func func, float start, float end)
	{
		this->start.x = start;
		this->end.x = end;

		graph.graph(func, start, end);

		this->start.y = graph.max.y;
		this->end.y = graph.min.y;

		scale.x = style.frameSize.x / (end - start);
		scale.y = style.frameSize.y / (this->end.y - this->start.y);

		graph.recompute();
		axis.recompute();
		grid.recompute();
	}

	void Plot::onStyleChanged()
	{
		initWindow();
		recompute();
	}

	void Plot::recompute()
	{
		setPosition(style.framePosition);

		frameShape.setSize(style.frameSize);
		frameShape.setOutlineThickness(-1.f);
		frameShape.setFillColor(Color::Transparent);
		frameShape.setOutlineColor(style.frameColor);

		scale.x = style.frameSize.x / (end.x - start.x);
		scale.y = style.frameSize.y / (end.y - start.y);
	}

	Coords Plot::toCoords(Values point) const
	{
		return Coords(
			(point.x - start.x) * scale.x,
			(point.y - start.y) * scale.y
		);
	}

	Values Plot::toValues(Coords point) const
	{
		return Values(
			point.x / scale.x + start.x,
			(point.y / scale.y + start.y)
		);
	}

	Coords Plot::toCoords(float vx, float vy) const
	{
		return toCoords(Values(vx, vy));
	}
	
	Values Plot::toValues(float cx, float cy) const
	{
		return toValues(Coords(cx, cy));
	}

	Coords Plot::rangeCoords(Coords point) const
	{
		return Coords(
			std::max(std::min(point.x - getPosition().x, style.frameSize.x), 0.f),
			std::max(std::min(point.y - getPosition().y, style.frameSize.y), 0.f)
		);
	}

	Coords Plot::rangeCoords(float cx, float cy) const
	{
		return rangeCoords(Coords(cx, cy));
	}
}