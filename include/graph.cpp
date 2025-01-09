#include "graph.h"

Graph::Graph(uint16_t width, uint16_t height) :
	winSize	(width, height),
	offset	(DEFAULT_GRAPH_OFFSET),
	margin	(DEFAULT_GRAPH_MARGIN),
	vbegin	(-10, -10),
	vend	(10, 10),
	window	(nullptr)
{
	series.reserve(10);
	backgroundColor = DEFAULT_COLORS.at("black");

	size = winSize - offset - margin;
	axis.reset(new Axis(*this, DEFAULT_COLORS.at("white")));
	grid.reset(new Grid(*this, DEFAULT_GRID_COUNT, DEFAULT_COLORS.at("dimgray")));
	cursor.reset(new Cursor(*this, offset, DEFAULT_COLORS.at("silver")));
	legend.reset(new Legend(*this, offset + DEFAULT_LEGEND_MARGIN, DEFAULT_COLORS.at("dimgray"), DEFAULT_COLORS.at("white")));

	vscale.x = size.x / (vend.x - vbegin.x);
	vscale.y = size.y / (vend.y - vbegin.y);
}

void Graph::changeTheme(bool lightTheme)
{
	if (lightTheme) {
		backgroundColor = DEFAULT_COLORS.at("white");
		axis->setColor(DEFAULT_COLORS.at("black"));
		grid->setColor(DEFAULT_COLORS.at("silver"));
		cursor->setColor(DEFAULT_COLORS.at("slategray"));
		legend->backgroundColor = DEFAULT_COLORS.at("aliceblue");
		legend->frameColor = DEFAULT_COLORS.at("black");
	}
	else {
		backgroundColor = DEFAULT_COLORS.at("aliceblue");
		axis->setColor(DEFAULT_COLORS.at("black"));
		grid->setColor(DEFAULT_COLORS.at("dimgray"));
		cursor->setColor(DEFAULT_COLORS.at("silver"));
		legend->backgroundColor = DEFAULT_COLORS.at("silver");
		legend->frameColor = DEFAULT_COLORS.at("dimgray");
	}
}

sf::Vector2f Graph::toPixels(float vx, float vy) const
{
	return sf::Vector2f(
		(vx - vbegin.x) * vscale.x + offset.x,
		size.y - (vy - vbegin.y) * vscale.y + offset.y
	);
}

sf::Vector2f Graph::toValues(float px, float py) const
{
	return sf::Vector2f(
		(px - offset.x) / vscale.x + vbegin.x,
		(size.y - py - offset.y) / vscale.y + vbegin.y
	);
}

sf::Vector2f Graph::toPixels(const sf::Vector2f& values) const
{
	return toPixels(values.x, values.y);
}

sf::Vector2f Graph::toValues(const sf::Vector2f& pixels) const
{
	return toValues(pixels.x, pixels.y);
}

std::pair<sf::Vector2f, sf::Vector2f> Graph::getBounds() const
{
	return std::make_pair(vbegin, vend);
}

void Graph::setBounds(const sf::Vector2f& vbeg, const sf::Vector2f& vend)
{
	setBounds(vbeg.x, vbeg.y, vend.x, vend.y);
}

void Graph::setBounds(float vxbeg, float vybeg, float vxend, float vyend)
{
	vbegin.x = vxbeg;
	vbegin.y = vybeg;
	vend.x = vxend;
	vend.y = vyend;
	recomputeScale();
}

bool Graph::isInside(float px, float py) const
{
	return offset.x <= px && px <= offset.x + size.x
		&& offset.y <= py && py <= offset.y + size.y;
}

bool Graph::isInside(const sf::Vector2f& pixels) const
{
	return isInside(pixels.x, pixels.y);
}

const sf::Vector2f& Graph::getPosition() const
{
	return offset;
}

void Graph::setPosition(const sf::Vector2f& pos)
{
	setPosition(pos.x, pos.y);
}

void Graph::setPosition(float x, float y)
{
	offset.x = x;
	offset.y = y;
	recomputeFrame();
}

const sf::Vector2f& Graph::getSize() const
{
	return size;
}

void Graph::setSize(const sf::Vector2f& newsize)
{
	size = newsize;
	recomputeFrame();
}

const sf::Vector2f& Graph::getWindowSize() const
{
	return winSize;
}

void Graph::setWindowSize(const sf::Vector2f& newsize)
{
	winSize = newsize;
	size = winSize - offset - margin;
	recomputeFrame();
}

const sf::Font& Graph::getFont() const
{
	return font;
}

void Graph::loadFont(const std::string& path)
{
	font.loadFromFile(path);
}

void Graph::plot(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const std::string& name, LineStyle style, float lineThickness)
{
	auto label = name.empty() ? "Graph " + std::to_string(series.size()) : name;
	auto color = DEFAULT_COLORS.at(DEFAULT_GRAPH_COLORS_STR[series.size() % DEFAULT_GRAPH_COLORS_STR.size()]);
	plot(valuesX, valuesY, label, color, style, lineThickness);
}

void Graph::plot(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const std::string& name, const sf::Color& color, LineStyle style, float lineThickness)
{
	onSeriesAppend(valuesX, valuesY, color, name);
	series.emplace_back(new Series(valuesX, valuesY, std::make_unique<LineArtist>(LineArtist(style, lineThickness)), color, name));
}

void Graph::bar(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const std::string& name, float barWidth)
{
	auto label = name.empty() ? "Graph " + std::to_string(series.size()) : name;
	auto color = DEFAULT_COLORS.at(DEFAULT_GRAPH_COLORS_STR[series.size() % DEFAULT_GRAPH_COLORS_STR.size()]);
	bar(valuesX, valuesY, label, color, barWidth);
}

void Graph::bar(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const std::string& name, const sf::Color& color, float barWidth)
{
	onSeriesAppend(valuesX, valuesY, color, name);
	series.emplace_back(new Series(valuesX, valuesY, std::make_unique<BarArtist>(BarArtist(barWidth)), color, name));
}

void Graph::scatter(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const std::string& name, float dotRadius)
{
	auto label = name.empty() ? "Graph " + std::to_string(series.size()) : name;
	auto color = DEFAULT_COLORS.at(DEFAULT_GRAPH_COLORS_STR[series.size() % DEFAULT_GRAPH_COLORS_STR.size()]);
	scatter(valuesX, valuesY, label, color, dotRadius);
}

void Graph::scatter(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const std::string& name, const sf::Color& color, float dotRadius)
{
	onSeriesAppend(valuesX, valuesY, color, name);
	series.emplace_back(new Series(valuesX, valuesY, std::make_unique<ScatterArtist>(ScatterArtist(dotRadius)), color, name));
}

void Graph::init()
{
	if (!window)
		window.reset(new sf::RenderWindow(sf::VideoMode(winSize.x, winSize.y), ""));
}

bool Graph::show()
{
	bool opened = window->isOpen();
	if (opened) {
		opened = processEvents();
		if (opened) render();
	}
	return opened;
}

void Graph::onSeriesAppend(const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color, const std::string& name)
{
	auto [minitX, maxitX] = std::minmax_element(valuesX.begin(), valuesX.end());
	auto [minitY, maxitY] = std::minmax_element(valuesY.begin(), valuesY.end());
	float minvX = (*minitX) != 0 ? (*minitX) - std::abs(*minitX) * DEFAULT_VALUES_MARGIN_PERCENTAGE : -1.f;
	float maxvX = (*maxitX) != 0 ? (*maxitX) + std::abs(*maxitX) * DEFAULT_VALUES_MARGIN_PERCENTAGE : +1.f;
	float minvY = (*minitY) != 0 ? (*minitY) - std::abs(*minitY) * DEFAULT_VALUES_MARGIN_PERCENTAGE : -1.f;
	float maxvY = (*maxitY) != 0 ? (*maxitY) + std::abs(*maxitY) * DEFAULT_VALUES_MARGIN_PERCENTAGE : +1.f;

	if (!series.empty())
	{
		auto newBegin = sf::Vector2f(
			std::min(minvX, vbegin.x),
			std::min(minvY, vbegin.y)
		);
		auto newEnd = sf::Vector2f(
			std::max(maxvX, vend.x),
			std::max(maxvY, vend.y)
		);
		if (newBegin != vbegin || newEnd != newEnd)
			setBounds(newBegin, newEnd);
	}
	else setBounds(minvX, minvY, maxvX, maxvY);
	legend->addItem(name, color);
}

void Graph::recomputeFrame()
{
	recomputeScale();
	grid->recompute();
	cursor->recompute();
}

void Graph::recomputeScale()
{
	vscale.x = size.x / (vend.x - vbegin.x);
	vscale.y = size.y / (vend.y - vbegin.y);
}

bool Graph::processEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
			window.reset();
			return false;
		}
		if (event.type == sf::Event::MouseMoved) {
			cursor->setPosition(
				std::min(std::max(offset.x, (float)event.mouseMove.x), size.x + offset.x),
				std::min(std::max(offset.y, (float)event.mouseMove.y), size.y + offset.y)
			);
		}
	}
	return true;
}

void Graph::render()
{
	window->clear(backgroundColor);

	if (showGraph)
		for (const auto& data : series)
			data->draw(*window, *this);

	if (showGrid)   grid->draw(*window);
	if (showCursor) cursor->draw(*window);
	if (showAxis)   axis->draw(*window);
	if (showLegend) legend->draw(*window);
	window->display();
}
