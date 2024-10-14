#pragma once
#include "locator.h"

class Axis :
	public PlotObject
{
	friend class Plotter;
public:
	enum Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	Axis(Plot* layout, Orientation orientation, Label label = Label());

	void setColor(sf::Color color);

	Orientation getOrientation() const;
	float getLength() const;

	void recompute() override;

	Locator		locator;
private:
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Label		label;
	float		length;
	Orientation	orientation;
};