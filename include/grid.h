#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
	friend class Graph;
public:

	const sf::Color& getColor() const;
	void setColor(const sf::Color& color);

	const sf::Vector2i& getCount() const;
	void setCount(const sf::Vector2i& count);

private:

	Grid(
		const Graph& layout,
		const sf::Vector2i& count,
		const sf::Color& color
	);

	void recompute();

	void draw(sf::RenderWindow& window);

	const Graph& layout;
	sf::Vector2i count;
	sf::Color color;
	sf::VertexArray linesH;
	sf::VertexArray linesV;
};