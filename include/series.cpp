#include "series.h"
#include "graph.h"

const sf::Color& Series::getColor() const
{
    return color;
}

void Series::setColor(const sf::Color& color)
{
    this->color = color;
}

const std::string& Series::getName() const
{
    return name;
}

void Series::setName(const std::string& name)
{
    this->name = name;
}

Series::Series(
	const std::vector<float>& xarray,
	const std::vector<float>& yarray,
	std::unique_ptr<Artist> artist,
	const sf::Color& color,
	const std::string& name
) :
	valuesX(xarray),
	valuesY(yarray),
	artist(std::move(artist)),
	color(color),
	name(name)
{
}

void Series::draw(sf::RenderWindow& window, const Graph& graph)
{
	artist->draw(window, graph, valuesX, valuesY, color);
}
