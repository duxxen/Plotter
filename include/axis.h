#pragma once
#include "common.hpp"

class Axis : public sf::Drawable
{
	friend class Plot;
	friend class Plotter;
public:
	Axis(Plot* layout);

private:

	void recompute();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	PlotPointer				layout;
	sf::VertexArray			marksX;
	sf::VertexArray			marksY;
	std::vector<sf::Text>	valuesX;
	std::vector<sf::Text>	valuesY;
};