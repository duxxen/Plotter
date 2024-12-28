#include "cursor.h"
#include "graph.h"

const sf::Color& Cursor::getColor() const
{
    return color;
}

void Cursor::setColor(const sf::Color& color)
{
    this->color = color;
    for (size_t i = 0; i < lines.getVertexCount(); i++)
        lines[i].color = color;
}

const sf::Vector2f& Cursor::getPosition() const
{
    return position;
}

void Cursor::setPosition(const sf::Vector2f& position)
{
    setPosition(position.x, position.y);
}

void Cursor::setPosition(float px, float py)
{
    position.x = px;
    position.y = py;
    lines[0].position.y = py;
    lines[1].position.y = py;
    lines[2].position.x = px;
    lines[3].position.x = px;
}

Cursor::Cursor(
    const Graph& layout,
    const sf::Vector2f& position,
    const sf::Color& color
) :
    layout(layout),
    position(position),
    color(color),
    lines(sf::Lines, 4U)
{
    recompute();
}

void Cursor::recompute()
{
    auto offset = layout.getPosition();
    auto length = layout.getSize();
    lines[0] = sf::Vertex(sf::Vector2f(offset.x, position.y), color);
    lines[1] = sf::Vertex(sf::Vector2f(offset.x + length.x, position.y), color);
    lines[2] = sf::Vertex(sf::Vector2f(position.x, offset.y), color);
    lines[3] = sf::Vertex(sf::Vector2f(position.x, offset.y + length.y), color);
}

void Cursor::draw(sf::RenderWindow& window)
{
    window.draw(lines);
}
