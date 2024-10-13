#pragma once
#include "common.hpp"
#include "locator.h"

class Axis : public sf::Drawable
{
	friend class Plot;
	friend class Locator;
public:
	Axis(Plot* layout, bool isX = true);

private:

	void recompute();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	float				length;
	const Plot*			layout;
	const bool			horizontal;
	const sf::Transform orientation;
	Locator				locator;
};
