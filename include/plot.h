#pragma once
#include "common.hpp"
#include "axis.h"

class Plot : public sf::Drawable, public sf::Transformable
{
	friend class Axis;
	friend class Plotter;
public:

	Plot(WindowFrame* layout);
	void adjust(float aleft, float atop, float aright, float abottom);

private:

	float toCoordsX(float vx) const;
	float toCoordsY(float vx) const;
	float toValuesX(float cx) const;
	float toValuesY(float cx) const;
	
	sf::Vector2f toCoords(sf::Vector2f values) const;
	sf::Vector2f toValues(sf::Vector2f coords) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	sf::Vector2i		gridSize	{ 5, 5 };
	sf::Vector2f		valuesStart	{ 0, 0 };
	sf::Vector2f		valuesEnd	{ 1, 1 };
	sf::Vector2f		valuesScale;

	WindowFramePointer	layout;
	sf::RectangleShape	frame;
	Axis				axis;
};