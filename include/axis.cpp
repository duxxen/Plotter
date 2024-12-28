#include "axis.h"
#include "graph.h"

const sf::Color& Axis::getColor() const
{
    return color;
}

void Axis::setColor(const sf::Color& color)
{
    this->color = color;
}

bool Axis::isCentered() const
{
    return centered;
}

void Axis::setCentered(bool centered)
{
	this->centered = centered;
}

Axis::Axis(
	const Graph& layout,
	const sf::Color& color,
	bool centered
) :
	layout	(layout),
	color	(color)
{
	setCentered(centered);
}

void Axis::draw(sf::RenderWindow& window)
{
	if (centered)	drawCentered(window);
	else			drawFramed(window);
}

void Axis::drawCentered(sf::RenderWindow& window)
{
	auto offset = layout.getPosition();
	auto length = layout.getSize();
	auto center = offset + (length / 2.f);

	sf::VertexArray lines(sf::Lines, 4U);
	lines[0] = sf::Vertex(sf::Vector2f(offset.x, center.y), color);
	lines[1] = sf::Vertex(sf::Vector2f(offset.x + length.x, center.y), color);
	lines[2] = sf::Vertex(sf::Vector2f(center.x, offset.y), color);
	lines[3] = sf::Vertex(sf::Vector2f(center.x, offset.y + length.y), color);

	window.draw(lines);
}

void Axis::drawFramed(sf::RenderWindow& window)
{
	auto offset = layout.getPosition();
	auto length = layout.getSize();
	
	sf::VertexArray lines(sf::LineStrip, 5U);
	lines[0] = sf::Vertex(offset, color);
	lines[1] = sf::Vertex(sf::Vector2f(offset.x + length.x, offset.y), color);
	lines[2] = sf::Vertex(sf::Vector2f(offset.x + length.x, offset.y + length.y), color);
	lines[3] = sf::Vertex(sf::Vector2f(offset.x, offset.y + length.y), color);
	lines[4] = sf::Vertex(offset, color);

	window.draw(lines);
}
