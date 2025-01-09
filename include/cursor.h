#pragma once
#include "common.hpp"

class Cursor
{
	friend class Graph;
public:

	const sf::Color& getColor() const;
	void setColor(const sf::Color& color);

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	void setPosition(float px, float py);

private:
	Cursor(
		const Graph& layout,
		const sf::Vector2f& position,
		const sf::Color& color
	);

	void recompute();
	void draw(sf::RenderWindow& window);

	const Graph& layout;
	sf::Vector2f position;
	sf::Color color;
	sf::VertexArray lines;
};

