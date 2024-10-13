#include "../include/plot.h"
#include "../include/window.h"

Plot::Plot(Window* layout) :
	layout	(layout),
	axisX	(this),
	axisY	(this, false)
{
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::Black);
	frame.setOutlineThickness(1.f);
	scale(1, -1);
	adjust(.125, .6, .9, .12);
}

void Plot::adjust(float aleft, float atop, float aright, float abottom)
{
	auto wsize = layout->dpi * layout->size;
	auto fposition = sf::Vector2f(
		aleft * wsize.x,
		atop * wsize.y
	);
	auto fsize = sf::Vector2f(
		aright * wsize.x - fposition.x,
		abottom * wsize.y + fposition.y
	);

	frame.setSize(fsize);
	setPosition(fposition);
	axisX.recompute();
	axisY.recompute();
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(frame, states);
	target.draw(axisX, states);
	target.draw(axisY, states);
}


