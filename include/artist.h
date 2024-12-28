#pragma once
#include <SFML/Graphics.hpp>

class Graph;

class Artist
{
public:
	virtual ~Artist() = default;
	virtual void draw(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	) = 0;
};

class LineArtist : public Artist
{
public:
	void draw(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	) override;
};