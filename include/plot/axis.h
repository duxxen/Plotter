#pragma once
#include "locator.h"

class Axis :
	public PlotObject
{
public:
	enum Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	Axis(Plot* layout, Orientation orientation, Label label = Label());
	
	Locator		locator;
private:

	void recompute() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Label		label;
	float		length;
	Orientation orientation;
};