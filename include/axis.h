#pragma once
#include "common.hpp"

class Axis : public sf::Drawable
{
	friend class Plot;
public:
	Axis(Plot* layout);

private:

	void recompute();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	PlotPointer		layout;
	sf::VertexArray	marksX;
	sf::VertexArray	marksY;
};