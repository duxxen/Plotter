#pragma once
#include "main/Common.hpp"
#include "main/LineStyle.hpp"
#include "main/PlotStyle.hpp"
#include "utility/ToString.hpp"

#include <iostream>

namespace Plotter
{
	class Plot
	{
	public:

		Plot(std::string name = "Plot", PlotProperties plotStyle = PlotProperties(), LineProperties lineStyle = LineProperties());

		void plot(std::vector<float> vx, std::vector<float> vy);
		void plot(std::function<float(float)> func, float xFrom, float xTo, 
			bool yAuto = true, float yFrom = 0, float yTo = 0);

		void run();

	private:

		sf::Vector2f toCoords(float vx, float vy) const;
		sf::Vector2f toCoords(sf::Vector2f v) const;

		sf::Vector2f toValues(float cx, float cy) const;
		sf::Vector2f toValues(sf::Vector2f c) const;

		void calculatePoints1(std::vector<float> vx, std::vector<float> vy);
		void calculatePoints2(float xFrom, float xTo, bool yAuto = true, float yFrom = 0, float yTo = 0);

		void recompute();
		void recomputePlot();
		void recomputeGrid();
		void recomputeAxis();
		void recomputeText();
		void recomputeFrame();
		void recomputeCursor();

		void processEvents();
		void render();

		LineProperties				lStyle;
		PlotProperties				pStyle;

		std::vector<sf::Vector2f>	points;		// Stored points (raw)
		sf::Vector2f				mins;		// minimums of points (raw)
		sf::Vector2f				maxs;		// maximums of points (raw)

		std::function<float(float)>	func;

		sf::RenderWindow			window;		
		//std::thread					thread;		// Calculation thread

		sf::VertexArray				gLinesV;	// Grid lines (vertical)
		sf::VertexArray				gLinesH;	// Grid lines (horizontal)
		sf::VertexArray				aLines;		// Axis lines
		sf::VertexArray				fLines;		// Frame lines
		sf::VertexArray				pLines;		// Plot lines
		sf::VertexArray				vLines;		// Volume lines
		sf::VertexArray				cLines;		// Cursor lines
		std::vector<sf::Text>		tVectV;		// Vertical text
		std::vector<sf::Text>		tVectH;		// Horizontal text
		sf::Text					cText;		// Cursor text

		// Transform variables
		float left, right;
		float top, bot;

		// Mouse
		sf::Vector2i mousePixels;
		sf::Vector2f mouseCoords;
		sf::Vector2f cursorCoords;
		bool rmbPressed;
	};
}

Plotter::Plot::Plot(std::string name, PlotProperties plotStyle, LineProperties lineStyle)
{
	window.create(sf::VideoMode(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT), name);
	window.setMouseCursorVisible(false);

	gLinesV.setPrimitiveType(sf::Lines);
	gLinesH.setPrimitiveType(sf::Lines);
	aLines.setPrimitiveType(sf::Lines);
	cLines.setPrimitiveType(sf::Lines);
	fLines.setPrimitiveType(sf::LineStrip);
	pLines.setPrimitiveType(sf::LineStrip);
	vLines.setPrimitiveType(sf::TriangleStrip);

	fLines.resize(5);
	aLines.resize(4);
	cLines.resize(4);

	pStyle = plotStyle;
	lStyle = lineStyle;

	left = right = 0;
	top = bot = 0;
}

void Plotter::Plot::plot(std::vector<float> vx, std::vector<float> vy)
{
	assert(vx.size() == vy.size());

	//thread = std::thread(&Plot::calculatePoints1, this, vx, vy);
	calculatePoints1(vx, vy);
}

void Plotter::Plot::plot(std::function<float(float)> func, float xFrom, float xTo, bool yAuto, float yFrom, float yTo)
{
	this->func = func;
	//thread = std::thread(&Plot::calculatePoints2, this, xFrom, xTo, yAuto, yFrom, yTo);
	calculatePoints2(xFrom, xTo, yAuto, yFrom, yTo);
}

inline sf::Vector2f Plotter::Plot::toCoords(float vx, float vy) const
{
	auto spacingX = (right - left) / (maxs.x - mins.x);
	auto spacingY = (bot - top) / (maxs.y - mins.y);

	auto offsetX = -mins.x * spacingX + left;
	auto offsetY = -mins.y * spacingY + (mins.y == 0 ? bot : top);

	return sf::Vector2f(
		spacingX * vx + offsetX,
		-spacingY * vy + offsetY
	);
}

inline sf::Vector2f Plotter::Plot::toCoords(sf::Vector2f v) const
{
	return toCoords(v.x, v.y);
}

inline sf::Vector2f Plotter::Plot::toValues(float cx, float cy) const
{
	auto spacingX = (right - left) / (maxs.x - mins.x);
	auto spacingY = (bot - top) / (maxs.y - mins.y);

	auto offsetX = -mins.x * spacingX + left;
	auto offsetY = -mins.y * spacingY + (mins.y == 0 ? bot : top);

	return sf::Vector2f(
		(cx - offsetX) / spacingX,
		-(cy - offsetY) / spacingY

	);
}

inline sf::Vector2f Plotter::Plot::toValues(sf::Vector2f c) const
{
	return toValues(c.x, c.y);
}

inline void Plotter::Plot::calculatePoints1(std::vector<float> vx, std::vector<float> vy)
{
	for (int i = 0; i < vx.size(); i++)
	{
		mins = sf::Vector2f(std::min(vx[i], mins.x), std::min(vy[i], mins.y));
		maxs = sf::Vector2f(std::max(vx[i], maxs.x), std::max(vy[i], maxs.y));
		points.push_back(sf::Vector2f(vx[i], vy[i]));
	}

	recompute();
}

inline void Plotter::Plot::calculatePoints2(float xFrom, float xTo, bool yAuto, float yFrom, float yTo)
{
	points.clear();

	mins.x = std::min(xFrom, xTo);
	maxs.x = std::max(xFrom, xTo);
	if (yAuto == false)
	{
		mins.y = std::min(yFrom, yTo);
		maxs.y = std::max(yFrom, yTo);
	}

	auto step = (maxs.x - mins.x) / pStyle.pointCount;

	for (int i = 0; i < pStyle.pointCount; i++)
	{
		auto x = mins.x + step * i;
		auto y = func(x);
		points.push_back(sf::Vector2f(x, y));

		if (yAuto)
		{
			mins.y = std::min(mins.y, y);
			maxs.y = std::max(maxs.y, y);
		}
	}

	recompute();
}

inline void Plotter::Plot::recompute()
{
	left = pStyle.indent;
	right = pStyle.width - pStyle.indent;
	top = pStyle.indent;
	bot = pStyle.height - pStyle.indent;

	recomputeFrame();
	recomputeText();
	recomputeGrid();
	recomputeAxis();
	recomputePlot();
}

inline void Plotter::Plot::recomputePlot()
{
	auto lColor = sf::Color(
		lStyle.lColorR,
		lStyle.lColorG,
		lStyle.lColorB,
		lStyle.lColorA
	);

	auto vColor = sf::Color(
		lStyle.vColorR,
		lStyle.vColorG,
		lStyle.vColorB,
		lStyle.vColorA
	);

	pLines.resize(points.size());
	vLines.resize(points.size());
	for (int i = 0; i < points.size(); i++)
	{
		auto crdi = toCoords(points[i].x, points[i].y);
		crdi.x = std::min(std::max(left, crdi.x), right);
		crdi.y = std::min(std::max(top, crdi.y), bot);
		
		pLines[i] = sf::Vertex(crdi, lColor);
		
		if (i % 2 == 0 && i < points.size() - 1)
		{
			vLines[i] = sf::Vertex(toCoords(points[i].x, 0), vColor);
			vLines[i + 1] = sf::Vertex(crdi, vColor);
		}
	}
}

inline void Plotter::Plot::recomputeGrid()
{
	auto spacingX = (right - left) / pStyle.gCountX;
	auto spacingY = (bot - top) / pStyle.gCountY;

	auto color = sf::Color(
		pStyle.gColorR,
		pStyle.gColorG,
		pStyle.gColorB,
		pStyle.gColorA
	);

	gLinesV.resize(2 * pStyle.gCountX);
	gLinesH.resize(2 * pStyle.gCountY);

	for (int x = 0; x < pStyle.gCountX - 1; x++)
	{
		gLinesV[2 * x] = sf::Vertex(sf::Vector2f(left + (x + 1) * spacingX, top), color);
		gLinesV[2 * x + 1] = sf::Vertex(sf::Vector2f(left + (x + 1) * spacingX, bot), color);
	}

	for (int y = 0; y < pStyle.gCountY - 1; y++)
	{
		gLinesH[2 * y] = sf::Vertex(sf::Vector2f(left, top + (y + 1) * spacingY), color);
		gLinesH[2 * y + 1] = sf::Vertex(sf::Vector2f(right, top + (y + 1) * spacingY), color);
	}
}

inline void Plotter::Plot::recomputeAxis()
{
	float posx = pStyle.centerAxis ? (right + left) / 2 : left;
	float posy = pStyle.centerAxis ? (bot + top) / 2 : bot; 

	auto color = sf::Color(
		pStyle.aColorR,
		pStyle.aColorG,
		pStyle.aColorB,
		pStyle.aColorA
	);

	aLines[0] = sf::Vertex(sf::Vector2f(posx, top), color);
	aLines[1] = sf::Vertex(sf::Vector2f(posx, bot), color);
	aLines[2] = sf::Vertex(sf::Vector2f(left, posy), color);
	aLines[3] = sf::Vertex(sf::Vector2f(right, posy), color);
}

inline void Plotter::Plot::recomputeText()
{
	auto spacingX = (right - left) / pStyle.gCountX;
	auto spacingY = (bot - top) / pStyle.gCountY;

	auto vScaleX = (maxs.x - mins.x) / pStyle.gCountX;
	auto vScaleY = (maxs.y - mins.y) / pStyle.gCountX;

	float posx = pStyle.centerAxis ? (right + left) / 2 : left;
	float posy = pStyle.centerAxis ? (bot + top) / 2 : bot;

	auto color = sf::Color(
		pStyle.tColorR,
		pStyle.tColorG,
		pStyle.tColorB,
		pStyle.tColorA
	);

	tVectH.resize(pStyle.gCountX);
	tVectV.resize(pStyle.gCountY);

	for (int x = 0; x < pStyle.gCountX; x++)
	{
		auto vX = mins.x + vScaleX * x;
		if (vX < 0.01 && vX > -0.01)
			vX = 0;

		tVectH[x] = sf::Text(toString(vX), pStyle.font, pStyle.charSize);
		tVectH[x].setPosition(pStyle.textIndent + x * spacingX, posy);
		tVectH[x].setFillColor(color);
	}

	for (int y = 0; y < pStyle.gCountY; y++)
	{
		auto vY = maxs.y - vScaleY * y;
		if (vY < 0.01 && vY > -0.01)
			vY = 0;

		tVectV[y] = sf::Text(toString(vY), pStyle.font, pStyle.charSize);
		tVectV[y].setPosition(posx, pStyle.textIndent + y * spacingY);
		tVectV[y].setFillColor(color);
	}

	cText.setFillColor(color);
}

inline void Plotter::Plot::recomputeFrame()
{
	auto color = sf::Color(
		pStyle.fColorR,
		pStyle.fColorG,
		pStyle.fColorB,
		pStyle.fColorA
	);

	fLines[0] = sf::Vertex(sf::Vector2f(left, bot), color);
	fLines[1] = sf::Vertex(sf::Vector2f(left, top), color);
	fLines[2] = sf::Vertex(sf::Vector2f(right, top), color);
	fLines[3] = sf::Vertex(sf::Vector2f(right, bot), color);
	fLines[4] = sf::Vertex(sf::Vector2f(left, bot), color);
}

inline void Plotter::Plot::recomputeCursor()
{
	auto color = sf::Color(
		pStyle.cColorR,
		pStyle.cColorG,
		pStyle.cColorB,
		pStyle.cColorA
	);

	auto cValue = toValues(cursorCoords.x, cursorCoords.y);

	auto posx = std::min(std::max(left, cursorCoords.x), right);
	auto posy = std::min(std::max(top, cursorCoords.y), bot);

	cLines[0] = sf::Vertex(sf::Vector2f(posx, top), color);
	cLines[1] = sf::Vertex(sf::Vector2f(posx, bot), color);
	cLines[2] = sf::Vertex(sf::Vector2f(left, posy), color);
	cLines[3] = sf::Vertex(sf::Vector2f(right, posy), color);

	posx = std::min(std::max(left + 2 *  pStyle.textIndent, posx), right - 5 * pStyle.textIndent);
	posy = std::min(std::max(top, posy), bot - 2 * pStyle.textIndent);

	cText.setFont(pStyle.font);
	cText.setCharacterSize(pStyle.charSize);
	cText.setString(toString(cValue.x) + ", " + toString(cValue.y));
	cText.setPosition(sf::Vector2f(posx, posy));
}

void Plotter::Plot::run()
{
	if (window.isOpen())
	{
		processEvents();
		render();
	}
}

void Plotter::Plot::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		float tempX = 0;
		float tempY = 0;

		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseMoved:
			mousePixels = sf::Mouse::getPosition(window);
			mouseCoords = window.mapPixelToCoords(mousePixels);

			if (rmbPressed)
			{
				tempX = toValues(mouseCoords).x;
				tempY = func(tempX);
				cursorCoords = toCoords(tempX, tempY);
			}
			else
				cursorCoords = mouseCoords;

			recomputeCursor();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right)
				rmbPressed = true;
			break;

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Right)
				rmbPressed = false;
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code)
			{
			case sf::Keyboard::Right:
				maxs.x += 1;
				if (event.key.shift)
					mins.x += 1;
				else if (event.key.alt)
					maxs.x -= 2;
				break;

			case sf::Keyboard::Left:
				mins.x -= 1;
				if (event.key.shift)
					maxs.x -= 1;
				else if (event.key.alt)
					mins.x += 2;
				break;

			case sf::Keyboard::Up:
				mins.y += 1;
				if (event.key.shift)
					maxs.y += 1;
				else if (event.key.alt)
					mins.x -= 2;
				break;

			case sf::Keyboard::Down:
				mins.y -= 1;
				if (event.key.shift)
					maxs.y -= 1;
				else if (event.key.alt)
					mins.x += 2;
				break;

			default:
				break;
			}

			plot(func, mins.x, maxs.x, false, mins.y, maxs.y);

			break;

		default:
			break;
		}
	}
}

void Plotter::Plot::render()
{
	window.clear(sf::Color(
		pStyle.bColorR, 
		pStyle.bColorG, 
		pStyle.bColorB, 
		pStyle.bColorA
	));

	if (pStyle.showGrid)
	{
		window.draw(gLinesV);
		window.draw(gLinesH);
	}

	if (pStyle.showAxis)
	{
		window.draw(aLines);
		for (int i = 0; i < tVectV.size(); i++)
			window.draw(tVectV[i]);
		for (int i = 0; i < tVectH.size(); i++)
			window.draw(tVectH[i]);
	}

	window.draw(pLines);

	if (pStyle.showVolume)
		window.draw(vLines);

	if (pStyle.showCursor)
	{
		window.draw(cLines);
		window.draw(cText);
	}

	window.draw(fLines);
	window.display();
}