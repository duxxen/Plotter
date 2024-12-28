#include "grid.h"
#include "graph.h"

const sf::Color& Grid::getColor() const
{
    return color;
}

void Grid::setColor(const sf::Color& color)
{
    this->color = color;
}

const sf::Vector2i& Grid::getCount() const
{
    return count;
}

void Grid::setCount(const sf::Vector2i& count)
{
    this->count = count;
    linesV.resize(2 * (count.x + 1));
    linesH.resize(2 * (count.y + 1));
    recompute();
}

Grid::Grid(
    const Graph& layout,
    const sf::Vector2i& count,
    const sf::Color& color
) :
    layout  (layout),
    color   (color),
    count   (count),
    linesV  (sf::Lines, 2 * (count.x + 1)),
    linesH  (sf::Lines, 2 * (count.y + 1))
{
    recompute();
}

void Grid::recompute()
{
    sf::Vector2f size = layout.getSize();
    sf::Vector2f offset = layout.getPosition();
    sf::Vector2f step(
        size.x / (count.x - 1),
        size.y / (count.y - 1)
    );

    for (int x = 0; x <= count.x; x++)
    {
        linesV[2 * x] = sf::Vertex(offset + sf::Vector2f(x * step.x, 0), color);
        linesV[2 * x + 1] = sf::Vertex(offset + sf::Vector2f(x * step.x, size.y), color);
    }
    for (int y = 0; y <= count.y; y++)
    {
        linesH[2 * y] = sf::Vertex(offset + sf::Vector2f(0, y * step.y), color);
        linesH[2 * y + 1] = sf::Vertex(offset + sf::Vector2f(size.x, y * step.y), color);
    }
}

void Grid::draw(sf::RenderWindow& window)
{
    window.draw(linesH);
    window.draw(linesV);
}
