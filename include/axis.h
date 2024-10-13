#pragma once
#include "common.h"
#include "locator.h"

class Axis : public sf::Drawable, private sf::Transformable
{
	friend class Plot;
	friend class Locator;
public:
	Axis(Plot* layout, bool isX = true);

	Locator				locator;

private:

	void recompute();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const Plot*			layout;
	float				length;
	const bool			horizontal;
};
