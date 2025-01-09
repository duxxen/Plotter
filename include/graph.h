#pragma once
#include "axis.h"
#include "grid.h"
#include "series.h"
#include "cursor.h"
#include "legend.h"

class Graph
{
public:
	Graph(uint16_t width = DEFAULT_WIN_WIDTH, uint16_t height = DEFAULT_WIN_HEIGHT);

	void changeTheme(bool lightTheme);

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

	const sf::Font& getFont() const;
	void loadFont(const std::string& path);

	void plot(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const std::string& name = "",
		LineStyle style = LineStyle::Solid,
		float lineThickness = 2.0f
	);

	void plot(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const std::string& name,
		const sf::Color& color,
		LineStyle style = LineStyle::Solid,
		float lineThickness = 2.0f
	);

	void bar(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const std::string& name = "",
		float barWidth = 0.5f
	);

	void bar(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const std::string& name,
		const sf::Color& color,
		float barWidth = 0.5f
	);

	void scatter(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const std::string& name = "",
		float dotRadius = 5.0f
	);

	void scatter(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const std::string& name,
		const sf::Color& color,
		float dotRadius = 5.0f
	);

	void init();
	bool show();

	bool showGrid = true;
	bool showAxis = true;
	bool showGraph = true;
	bool showCursor = true;
	bool showLegend = true;

private:

	void onSeriesAppend(
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color,
		const std::string& name
	);

	void recomputeFrame();
	void recomputeScale();
	bool processEvents();
	void render();

	sf::Font font;
	sf::Color backgroundColor;

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
	std::unique_ptr<Legend> legend;
	std::vector<std::unique_ptr<Series>> series;
};