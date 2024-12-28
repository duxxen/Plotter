#pragma once
#include <SFML/Graphics.hpp>

class Axis
{
	friend class Graph;
public:
	const sf::Color& getColor() const;
	void setColor(const sf::Color& color);

	bool isCentered() const;
	void setCentered(bool centered);

private:
	Axis(
		const Graph& layout,
		const sf::Color& color,
		bool centered = false
	);

	void draw(sf::RenderWindow& window);
	void drawCentered(sf::RenderWindow& window);
	void drawFramed(sf::RenderWindow& window);

	const Graph& layout;
	bool centered;
	sf::Color color;
	sf::VertexArray lines;
};