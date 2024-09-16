#include "plot.h"

namespace Plotter
{
	//const Plot::PlotStyle Plot::DEFAULT_PLOT_STYLE;

	Plot::PlotStyle::PlotStyle(
		string windowName, 
		Coords windowSize, 
		Color backgroundColor,
		Color frameColor, 
		uint32_t pointCount) 
		:
		windowName(windowName),
		windowSize(windowSize),
		backgroundColor(backgroundColor),
		frameColor(frameColor),
		pointCount(pointCount)
	{
	}

	Plot::Plot(
		PlotStyle pstyle, 
		Axis::AxisStyle astyle,
		Grid::GridStyle gstyle,
		Cursor::CursorStyle cstyle,
		Title::TitleStyle tstyle)
		:
		Object	{ nullptr },
		axis	{ this, astyle },
		grid	{ this, gstyle, tstyle },
		cursor	{ this, cstyle, tstyle },
		style	{ pstyle }
	{
		init();
	}

	void Plot::setStyle(PlotStyle newStyle)
	{
		onStyleChanged(newStyle);
	}

	void Plot::setStyle(Axis::AxisStyle newStyle)
	{
		auto oldStyle = axis.style;
		axis.onStyleChanged(newStyle);

		if (newStyle.centered != oldStyle.centered)
			onAxisMove();
	}

	void Plot::setStyle(Cursor::CursorStyle newStyle)
	{
		cursor.onStyleChanged(newStyle);
	}

	void Plot::setStyle(Grid::GridStyle newStyle)
	{
		grid.onStyleChanged(newStyle);
	}

	void Plot::setStyle(Title::TitleStyle newStyle)
	{
		grid.onStyleChanged(newStyle);
		cursor.onStyleChanged(newStyle);
	}

	void Plot::setBoundsX(float start, float end)
	{
		this->start.x = start;
		this->end.x = end;

		for (auto& graph : graphs)
			graph.rebuild();

		if (axis.style.centered && toCoords(0, 0).x < DEFAULT_WIN_INDENT)
			onAxisMove();
		else
			recompute();
	}

	void Plot::setBoundsY(float start, float end)
	{
		this->start.y = end;					// Inverted
		this->end.y = start;
		yAuto = false;
		
		recompute();
	}

	void Plot::setBounds(Values start, Values end)
	{
		this->start = Coords(start.x, end.y);
		this->end = Coords(end.x, start.y);

		yAuto = false;

		for (auto& graph : graphs)
			graph.rebuild();

		if (axis.style.centered && toCoords(0, 0).x < DEFAULT_WIN_INDENT)
			onAxisMove();
		else
			recompute();
	}

	void Plot::plot(Func func, Graph::GraphStyle style)
	{
		if (graphs.empty())
			start.y = end.y = func(start.x);

		auto index = graphs.size();
		graphs.push_back(Graph(this, style));

		plot(index, func);
	}

	void Plot::plot(size_t index, Func func)
	{
		if (graphs.empty() || index >= graphs.size())
			throw -1;

		graphs[index].graph(func, start.x, end.x);

		if (yAuto)
		{
			start.y = (std::max(start.y, graphs[index].max.y));
			end.y = (std::min(end.y, graphs[index].min.y));
		}

		recompute();
	}

	void Plot::plot(Func func, float start, float end, Graph::GraphStyle style)
	{
		if (graphs.empty())
			this->start.y = this->end.y = func(start);

		auto index = graphs.size();
		graphs.push_back(Graph(this, style));

		plot(index, func, start, end);
	}

	void Plot::plot(size_t index, Func func, float start, float end)
	{
		if (graphs.empty() || index >= graphs.size())
			throw - 1;

		this->start.x = start;
		this->end.x = end;

		graphs[index].graph(func, start, end);

		if (yAuto)
		{
			this->start.y = (std::max(this->start.y, graphs[index].max.y));
			this->end.y = (std::min(this->end.y, graphs[index].min.y));
		}

		recompute();
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

			case sf::Event::Resized:
				onWindowResize(event.size.width, event.size.height);
				break;

			case sf::Event::MouseMoved:
				cursor.setPosition(rangeCoords(event.mouseMove.x, event.mouseMove.y));
				break;

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

	void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(grid, states);
		target.draw(axis, states);

		for (auto& graph : graphs)
			target.draw(graph, states);

		target.draw(cursor, states);

		if (cursor.style.flags & Cursor::CursorStyle::SHOW_TITLE)
			target.draw(cursor.title, states);

		for (auto& title : grid.titles)
			target.draw(title, states);

		target.draw(frameShape, states);
	}

	void Plot::onStyleChanged(PlotStyle nstyle)
	{
		auto ostyle = style;
		style = nstyle;

		if (ostyle.windowSize != style.windowSize)
			onWindowResize(style.windowSize.x, style.windowSize.y);

		if (ostyle.pointCount != style.pointCount)
			for (auto& graph : graphs)
			{
				graph.rebuild();
				graph.recompute();
			}
		
		window.setTitle(style.windowName);
		frameShape.setOutlineColor(style.frameColor);
	}

	void Plot::onWindowResize(float width, float height)
	{
		auto size = Coords(width, height);
		auto view = window.getView();
		auto resize = size - style.windowSize;

		style.windowSize = size;

		view.setSize(style.windowSize);
		view.setCenter(size / 2.f);
		window.setView(view);

		onFrameResize(frameSize.x + resize.x, frameSize.y + resize.y);
	}

	void Plot::onFrameResize(float width, float height)
	{
		frameSize.x = width;
		frameSize.y = height;
		frameShape.setSize(frameSize);

		recompute();
	}

	void Plot::onAxisMove()
	{
		auto pos = Coords(
			DEFAULT_WIN_INDENT,
			DEFAULT_WIN_INDENT
		);
		auto size = Coords(
			style.windowSize.x - 2 * DEFAULT_WIN_INDENT,
			style.windowSize.y - 2 * DEFAULT_WIN_INDENT
		);

		if (axis.style.centered == false || toCoords(0, 0).x < DEFAULT_WIN_INDENT)
		{
			size.x -= DEFAULT_FRAME_INDENT_LEFT;
			pos.x += DEFAULT_FRAME_INDENT_LEFT;
		}
		setPosition(pos.x, pos.y);
		onFrameResize(size.x, size.y);
	}

	void Plot::init()
	{
		window.create(sf::VideoMode(style.windowSize.x, style.windowSize.y), style.windowName);
		window.setMouseCursorVisible(false);

		start.x = -10;
		end.x = 10;
		start.y = 10;
		end.y = -10;

		setPosition(DEFAULT_WIN_INDENT, DEFAULT_WIN_INDENT);	
		frameSize.x = style.windowSize.x - 2 * DEFAULT_WIN_INDENT;
		frameSize.y = style.windowSize.y - 2 * DEFAULT_WIN_INDENT;

		if (!axis.style.centered)
		{
			frameSize.x -= DEFAULT_FRAME_INDENT_LEFT;
			move(DEFAULT_FRAME_INDENT_LEFT, 0);
		}

		scale.x = frameSize.x / (end.x - start.x);
		scale.y = frameSize.y / (end.y - start.y);

		frameShape.setSize(frameSize);
		frameShape.setOutlineThickness(-1.f);
		frameShape.setOutlineColor(style.frameColor);
		frameShape.setFillColor(sf::Color::Transparent);

		axis.init();
		grid.init();
		cursor.init();
	}

	void Plot::recompute()
	{
		scale = Coords(
			frameSize.x / (end.x - start.x),
			frameSize.y / (end.y - start.y)
		);

		axis.recompute();
		grid.recompute();
		cursor.recompute();
		for (auto& graph : graphs)
			graph.recompute();
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
			std::max(std::min(point.x - getPosition().x, frameSize.x), 0.f),
			std::max(std::min(point.y - getPosition().y, frameSize.y), 0.f)
		);
	}

	Coords Plot::rangeCoords(float cx, float cy) const
	{
		return rangeCoords(Coords(cx, cy));
	}

	
}