#pragma once
#include "common.h"
#include "axis.h"

class Plot : public sf::Drawable, private sf::Transformable
{
	friend class Locator;
	friend class Axis;
public:
	Plot(Window* layout);

	void adjust(float aleft, float aright, float atop, float abottom);
	void setBounds(float xs, float xe, float ys, float ye);

	Axis	axisX;
	Axis	axisY;

private:

	float toValuesX(float cx) const;
	float toValuesY(float cy) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const Window*		layout;
	sf::Vector2f		size;
	sf::VertexArray		frame;
	sf::RectangleShape	background;
	
	sf::Vector2f		valuesBegin;
	sf::Vector2f		valuesEnd;
	sf::Vector2f		valuesScale;
};