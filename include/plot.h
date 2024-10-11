#pragma once
#include "common.hpp"
#include "axis.h"

class Plot : public sf::Drawable, public sf::Transformable
{
	friend class Axis;
public:

	Plot(WindowFrame* layout);
	void adjust(float aleft, float atop, float aright, float abottom);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	sf::Vector2i		gridSpacing{ 5, 5 };

	WindowFramePointer	layout;
	sf::RectangleShape	frame;
	Axis				axis;
};