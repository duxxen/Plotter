#pragma once
#include <SFML/Graphics.hpp>
#include "axis.h"
#include "grid.h"
#include "series.h"
#include "cursor.h"

#define DEFAULT_WIN_WIDTH  800U
#define DEFAULT_WIN_HEIGHT 600U
#define DEFAULT_GRAPH_OFFSET { 30.f, 20.f }
#define DEFAULT_GRAPH_MARGIN { 20.f, 30.f }
#define DEFAULT_GRID_COUNT { 10, 10 }

#define DEFAULT_VALUES_MARGIN_PERCENTAGE 0.1f

class Graph
{
public:

	const std::vector<sf::Color> colors{
		sf::Color(0xff0000ff),	// red
		sf::Color(0x00ff00ff)	// blue
	};

	Graph(uint32_t width = DEFAULT_WIN_WIDTH, uint32_t height = DEFAULT_WIN_HEIGHT);

	sf::Vector2f toPixels(float vx, float vy) const;
	sf::Vector2f toValues(float px, float py) const;
	sf::Vector2f toPixels(const sf::Vector2f& values) const;
	sf::Vector2f toValues(const sf::Vector2f& pixels) const;

	std::pair<sf::Vector2f, sf::Vector2f> getBounds() const;
	void setBounds(const sf::Vector2f& vbeg, const sf::Vector2f& vend);
	void setBounds(float vxbeg, float vybeg, float vxend, float vyend);

	bool isInside(float px, float py) const;
	bool isInside(const sf::Vector2f& pixels) const;

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& pos);
	void setPosition(float x, float y);

	const sf::Vector2f& getSize() const;
	void setSize(const sf::Vector2f& newsize);
	const sf::Vector2f& getWindowSize() const;
	void setWindowSize(const sf::Vector2f& newsize);

	void plot(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		float lineThickness = 2.0f,
		LineStyle style = LineStyle::Solid,
		const sf::Color& color = sf::Color::Red,
		const std::string& name = ""
	);

	void bar(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		float barWidth = 0.5f,
		const sf::Color& color = sf::Color::Red,
		const std::string& name = ""
	);

	void scatter(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		float dotRadius = 5.0f,
		const sf::Color& color = sf::Color::Red,
		const std::string& name = ""
	);

	void init();
	bool show();

	bool showGrid = true;
	bool showAxis = true;
	bool showGraph = true;
	bool showCursor = true;

private:

	void onSeriesAppend(const std::vector<float>& valuesX, const std::vector<float>& valuesY);

	void recomputeFrame();
	void recomputeScale();
	bool processEvents();
	void render();

	std::unique_ptr<sf::RenderWindow> window;
	sf::Vector2f winSize;
	sf::Vector2f size;
	sf::Vector2f offset;
	sf::Vector2f margin;

	sf::Vector2f vscale;
	sf::Vector2f vbegin;
	sf::Vector2f vend;

	std::unique_ptr<Grid> grid;
	std::unique_ptr<Axis> axis;
	std::unique_ptr<Cursor> cursor;
	std::vector<std::unique_ptr<Series>> series;
};