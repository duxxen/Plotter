#pragma once
#include "locator.h"

class Axis :
	public PlotObject
{
	friend class Plotter;
public:

	Axis(Orientation orientation, Label label = Label());

	void setColor(sf::Color color);

	void recompute() override;

	Locator		locator;
private:
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Label		label;
	Orientation	orientation;
};