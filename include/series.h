#pragma once
#include "artist.h"

class Series
{
	friend class Graph;
public:

	const sf::Color& getColor() const;
	void setColor(const sf::Color& color);

	const std::string& getName() const;
	void setName(const std::string& name);

private:

	Series(
		const std::vector<float>& xarray, 
		const std::vector<float>& yarray, 
		std::unique_ptr<Artist> artist, 
		const sf::Color& color, 
		const std::string& name = ""
	);

	void draw(sf::RenderWindow& window, const Graph& graph);

	sf::Color	color;
	std::string name;
	std::vector<float> valuesX;
	std::vector<float> valuesY;
	std::unique_ptr<Artist> artist;
};