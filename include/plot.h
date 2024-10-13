#pragma once
#include "common.hpp"
#include "axis.h"

class Plot : public sf::Drawable, public sf::Transformable
{
	friend class Locator;
	friend class Axis;
public:
	Plot(Window* layout);

	void adjust(float aleft, float atop, float aright, float abottom);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const Window*		layout;
	sf::RectangleShape	frame;
	Axis				axisX;
	Axis				axisY;
};