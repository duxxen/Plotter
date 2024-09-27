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
		Func func,
		float start,
		float end,
		PlotStyle pstyle,
		Axis::AxisStyle astyle,
		Grid::GridStyle gstyle,
		Cursor::CursorStyle cstyle,
		Title::TitleStyle tstyle)
		:
		Object{ nullptr },
		axis{ this, astyle, tstyle },
		grid{ this, gstyle, tstyle },
		cursor{ this, cstyle, tstyle },
		style{ pstyle }
	{
		init();
		plot(func, start, end);
	}

	Plot::Plot(
		PlotStyle pstyle, 
		Axis::AxisStyle astyle,
		Grid::GridStyle gstyle,
		Cursor::CursorStyle cstyle,
		Title::TitleStyle tstyle)
		:
		Object	{ nullptr },
		axis	{ this, astyle, tstyle },
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

		if (oldStyle.centered != newStyle.centered)
		{
			recomputeFrame();
			recompute();
		}
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

	void Plot::enableAutoScaleY(bool enable)
	{
		yAuto = enable;
	}

	void Plot::setBoundsX(float start, float end)
	{
		this->start.x = start;
		this->end.x = end;
		scale.x = frameSize.x / abs(end - start);

		for (auto& graph : graphs)
			graph.rebuild();

		axis.recompute();
		recomputeFrame();
		recompute();
	}

	void Plot::setBoundsY(float start, float end)
	{
		this->start.y = start;
		this->end.y = end;
		scale.y = frameSize.y / abs(end - start);

		recompute();
	}

	void Plot::setBounds(Values start, Values end)
	{
		this->start.y = start.y;
		this->end.y = end.y;
		scale.y = frameSize.y / abs(end.y - start.y);

		setBoundsX(start.x, end.x);
	}

	void Plot::setBounds(float startX, float endX, float startY, float endY)
	{
		setBounds(Values(startX, startY), Values(endX, endY));
	}

	void Plot::plot(Func func)
	{
		plot(func, Graph::GraphStyle(
			DEFAULT_COLORS_ARRAY[graphs.size() % DEFAULT_COLORS_SIZE],
			Graph::DEFAULT_GRAPH_STYLE.flags,
			Graph::DEFAULT_GRAPH_STYLE.transparency
		));
	}

	void Plot::plot(Func func, Graph::GraphStyle style)
	{
		if (graphs.empty() && yAuto)
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
		
		if (yAuto)	setBoundsY(std::min(start.y, graphs[index].min.y), std::max(start.y, graphs[index].max.y));
		else		graphs[index].recompute();
	}

	void Plot::plot(Func func, float start, float end)
	{
		plot(func, start, end, Graph::GraphStyle(
			DEFAULT_COLORS_ARRAY[graphs.size() % DEFAULT_COLORS_SIZE],
			Graph::DEFAULT_GRAPH_STYLE.flags,
			Graph::DEFAULT_GRAPH_STYLE.transparency
		));
	}

	void Plot::plot(Func func, float start, float end, Graph::GraphStyle style)
	{
		if (graphs.empty() && yAuto)
			this->start.y = this->end.y = func(start);

		auto index = graphs.size();
		graphs.push_back(Graph(this, style));

		plot(index, func, start, end);
	}

	void Plot::plot(size_t index, Func func, float start, float end)
	{
		if (graphs.empty() || index >= graphs.size())
			throw - 1;

		graphs[index].graph(func, start, end);

		if (yAuto)
		{
			this->start.y = std::min(this->start.y, graphs[index].min.y);
			this->end.y = std::max(this->end.y, graphs[index].max.y);
			scale.y = frameSize.y / (this->end.y - this->start.y);
		}

		setBoundsX(start, end);
	}

	bool Plot::processEvents()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			auto maxf = 0;
			auto maxi = 0;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				resizeWindow(event.size.width, event.size.height);
				break;

			case sf::Event::MouseMoved:
				mouse = Coords(event.mouseMove.x, event.mouseMove.y) - getPosition();
				if (isInside(mouse))
				{
					cursor.setPosition(rangeCoords(mouse));
					window.setMouseCursorVisible(false);
				}
				else
					window.setMouseCursorVisible(true);

				break;

			case sf::Event::MouseButtonPressed:
				pressPosition = mouse;

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					if (isInside(mouse))
					{
						rebounding = true;
						areaShape.setPosition(mouse);
					}
					break;

				case sf::Mouse::Right:
					tracing = true;
					tracingGraph = nearestGraph();
					break;
					

				case sf::Mouse::Middle:
					grabbed = true;
					break;

				default:
					break;
				}
				
				break;

			case sf::Event::MouseButtonReleased:

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					rebounding = false;
					areaShape.setSize(Coords(0, 0));
					if (pressPosition != mouse)
						setBounds(
							toValues(std::min(pressPosition.x, mouse.x), std::max(pressPosition.y, mouse.y)),
							toValues(std::max(pressPosition.x, mouse.x), std::min(pressPosition.y, mouse.y))
						);
					break;

				case sf::Mouse::Right:
					tracing = false;
					tracingGraph = nullptr;
					break;
					 
				case sf::Mouse::Middle:
					grabbed = false;
					break;

				default:
					break;
				}
				break;

			case sf::Event::MouseWheelScrolled:
				zoom(event.mouseWheelScroll.delta);
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::R)
					setBounds(DEFAULT_PLOT_START, DEFAULT_PLOT_END);

				shift = event.key.shift;
				break;

			case sf::Event::KeyReleased:
				shift = event.key.shift;
				break;

			default:
				break;
			}
		}

		return window.isOpen();
	}

	void Plot::update()
	{
		if (isInside(mouse))
		{
			if (rebounding)
			{
				auto size = mouse - pressPosition;
				areaShape.setSize(size);
			}
			else if (tracing)
			{
				auto vx = toValues(mouse).x;
				auto vy = tracingGraph->function(vx);
				cursor.setPosition(rangeCoords(toCoords(vx, vy)));
				cursor.titleValues.setString(toString(vx) + ", " + toString(vy));
			}
			else if (grabbed)
			{
				auto offset = toValues(pressPosition) - toValues(mouse);
				pressPosition = mouse;

				if (shift)	setBoundsX(start.x + offset.x, end.x + offset.x);
				else		setBounds(start + offset, end + offset);
			}
		}
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
		target.draw(areaShape, states);

		if (!axis.style.nameX.isEmpty())
			target.draw(axis.nameX, states);
		if (!axis.style.nameY.isEmpty())
			target.draw(axis.nameY, states);

		if (cursor.style.flags & Cursor::CursorStyle::SHOW_TITLE)
			target.draw(cursor.titleValues, states);
		

		for (auto& title : grid.titles)
			target.draw(title, states);

		target.draw(frameShape, states);
	}

	void Plot::onStyleChanged(PlotStyle nstyle)
	{
		auto ostyle = style;
		style = nstyle;

		if (ostyle.pointCount != nstyle.pointCount)
			for (auto& graph : graphs)
			{
				graph.rebuild();
				graph.recompute();
			}

		if (ostyle.windowSize != nstyle.windowSize)
			resizeWindow(nstyle.windowSize.x, nstyle.windowSize.y);

		window.setTitle(nstyle.windowName);
		frameShape.setOutlineColor(nstyle.frameColor);
	}

	void Plot::resizeWindow(float width, float height)
	{
		auto view = window.getView();
		view.setSize(width, height);
		view.setCenter(width / 2.f, height / 2.f);
		window.setView(view);
		window.setSize(sf::Vector2u(width, height));

		recomputeFrame();
		recompute();
	}

	void Plot::recomputeFrame()
	{
		auto windowSize = window.getSize();
		auto indent = !axis.style.centered || axis.intersection.x <= DEFAULT_WIN_INDENT ? 
			Coords(DEFAULT_FRAME_INDENT_LEFT, DEFAULT_AXIS_NAME_INDENT) : Coords(0, 0);

		auto frameCoords = Coords(
			DEFAULT_WIN_INDENT + indent.x, 
			DEFAULT_WIN_INDENT
		);
		frameSize = Coords(
			windowSize.x - 2.f * DEFAULT_WIN_INDENT - indent.x,
			windowSize.y - 2.f * DEFAULT_WIN_INDENT - indent.y
		);
		scale = Values(
			frameSize.x / (end.x - start.x),
			frameSize.y / (end.y - start.y)
		);

		setPosition(frameCoords);
		frameShape.setSize(frameSize);
	}

	void Plot::init()
	{
		window.create(sf::VideoMode(style.windowSize.x, style.windowSize.y), style.windowName);

		frameShape.setOutlineThickness(1.f);
		frameShape.setFillColor(Color::Transparent);
		frameShape.setOutlineColor(style.frameColor);

		areaShape.setOutlineThickness(1.f);
		areaShape.setFillColor(Color(0x87ceeb40));
		areaShape.setOutlineColor(Color(0x87ceebff));

		axis.intersection = style.windowSize / 2.f;
		recomputeFrame();

		start = DEFAULT_PLOT_START;
		end = DEFAULT_PLOT_END;
		scale = Values(
			frameSize.x / (end.x - start.x),
			frameSize.y / (end.y - start.y)
		);

		axis.init();
		grid.init();
		cursor.init();
	}

	void Plot::recompute()
	{
		axis.recompute();
		grid.recompute();
		cursor.recompute();
		for (auto& graph : graphs)
			graph.recompute();
	}

	Graph* Plot::nearestGraph()
	{
		if (graphs.empty())
			return nullptr;

		auto values = toValues(mouse);
		int maxi = 0;
		float maxr = abs(graphs[maxi].function(values.x) - values.y);

		for (auto i = 1; i < graphs.size(); i++)
		{
			auto range = abs(graphs[i].function(values.x) - values.y);
			if (range < maxr)
			{
				maxr = range;
				maxi = i;
			}
		}

		return &graphs[maxi];
	}

	void Plot::zoom(float delta)
	{
		float zoom = delta < 0 ? DEFAULT_ZOOM_VALUE : 1.f / DEFAULT_ZOOM_VALUE;
		if (shift)	setBoundsX(zoom * start.x, zoom * end.x);
		else		setBounds(zoom * start, zoom * end);
	}

	Coords Plot::toCoords(Values point) const
	{
		return Coords(
			(point.x - start.x) * scale.x,
			-(point.y - end.y) * scale.y
		);
	}

	Values Plot::toValues(Coords point) const
	{
		return Values(
			point.x / scale.x + start.x,
			-point.y / scale.y + end.y
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
			std::max(std::min(point.x, frameSize.x), 0.f),
			std::max(std::min(point.y, frameSize.y), 0.f)
		);
	}

	Coords Plot::rangeCoords(float cx, float cy) const
	{
		return rangeCoords(Coords(cx, cy));
	}

	bool Plot::isInside(Coords point) const
	{
		return 0.f <= point.x && point.x <= frameSize.x
			&& 0.f <= point.y && point.y <= frameSize.y;
	}

	bool Plot::isInside(float cx, float cy) const
	{
		return isInside(Coords(cx, cy));
	}
}