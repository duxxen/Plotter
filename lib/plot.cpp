#include "../include/plot.h"
#include "../include/window.h"

Plot::Plot(Window* layout) :
	layout	(layout),
	axisX	(this),
	axisY	(this, false),
	frame(sf::LineStrip, 5)
{
	background.setFillColor(sf::Color::Transparent);
	
	setScale(1, -1);
	setBounds(0, 1, 0, 1);
	adjust(.125, .9, .88, .1);
}

void Plot::adjust(float aleft, float aright, float atop, float abottom)
{
	atop = 1.f - atop;
	abottom = 1.f - abottom;

	auto wsize = layout->dpi * layout->size;
	auto fleft = wsize.x * aleft;
	auto fbottom = wsize.y * abottom;

	size = sf::Vector2f(
		wsize.x * aright - fleft,
		fbottom - wsize.y * atop
	);
	
	frame[0] = frame[4] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black);
	frame[1] = sf::Vertex(sf::Vector2f(size.x, 0), sf::Color::Black);
	frame[2] = sf::Vertex(sf::Vector2f(size.x, size.y), sf::Color::Black);
	frame[3] = sf::Vertex(sf::Vector2f(0, size.y), sf::Color::Black);

	setPosition(fleft, fbottom);
	background.setSize(size);
	axisX.recompute();
	axisY.recompute();
}

void Plot::setBounds(float xs, float xe, float ys, float ye)
{
	valuesBegin = { xs, ys };
	valuesEnd = { xe, ye };
	valuesScale = sf::Vector2f(
		(xe - xs) / size.x,
		(ye - ys) / size.y
	);
}

float Plot::toValuesX(float cx) const
{
	return cx * valuesScale.x;
}

float Plot::toValuesY(float cy) const
{
	return cy * valuesScale.y;
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(frame, states);
	target.draw(axisX, states);
	target.draw(axisY, states);
}


