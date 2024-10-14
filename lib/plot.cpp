#include "../include/plot/plot.h"
#include "../include/window.h"
#include "../include/plotter.h"

Plot::Plot(Window* layout, sf::Vector2f aposlt, sf::Vector2f aposrb) :
	PlotObject	(layout),
	axisX		(this, Axis::HORIZONTAL),
	axisY		(this, Axis::VERTICAL),
	vbegin		(0, 0),
	vend		(1, 1),
	frame		(sf::LineStrip, 5)
{
	adjust(aposlt, aposrb);
}

Plot::Plot(Window* layout, float vxbegin, float vybegin, float vxend, float vyend, float aleft, float atop, float aright, float abottom) :
	PlotObject	(layout),
	axisX		(this, Axis::HORIZONTAL),
	axisY		(this, Axis::VERTICAL),
	vbegin		(vxbegin, vybegin),
	vend		(vxend, vyend),
	frame		(sf::LineStrip, 5)
{
	adjust(aleft, atop, aright, abottom);
}

Plot::Plot(Window* layout, sf::Vector2f vbegin, sf::Vector2f vend, sf::Vector2f aposlt, sf::Vector2f aposrb) : 
	PlotObject	(layout),
	axisX		(this, Axis::HORIZONTAL),
	axisY		(this, Axis::VERTICAL),
	vbegin		(vbegin),
	vend		(vend),
	frame		(sf::LineStrip, 5)
{
	adjust(aposlt, aposrb);
}

void Plot::adjust(float aleft, float atop, float aright, float abottom)
{
	auto window = static_cast<Window*>(toLayout());
	auto size = window->getWindowSize();
	auto position = sf::Vector2f(size.x * aleft, size.y * atop);
	auto fsize = sf::Vector2f(size.x * aright, size.y * abottom) - position;

	setPosition(position);
	setSize(fsize);

	recompute();
}

void Plot::adjust(sf::Vector2f aposlt, sf::Vector2f aposrb)
{
	adjust(aposlt.x, aposlt.y, aposrb.x, aposrb.y);
}

void Plot::setBounds(float vxbegin, float vybegin, float vxend, float vyend)
{
	vbegin = sf::Vector2f(vxbegin, vybegin);
	vend = sf::Vector2f(vxend, vyend);
	recompute();
}

void Plot::setBounds(sf::Vector2f vbegin, sf::Vector2f vend)
{
	setBounds(vbegin.x, vbegin.y, vend.x, vend.y);
}

// c = v / s
// v = c * s
float Plot::toValuesX(float cx) const
{
	return cx * vscale.x;
}

float Plot::toValuesY(float cy) const
{
	return cy * vscale.y;
}

sf::Vector2f Plot::toValues(sf::Vector2f coords) const
{
	return sf::Vector2f(toValuesX(coords.x), toValuesY(coords.y));
}

float Plot::toCoordsX(float vx) const
{
	return vx / vscale.x;
}

float Plot::toCoordsY(float vy) const
{
	return vy / vscale.y;
}

sf::Vector2f Plot::toCoords(sf::Vector2f values) const
{
	return sf::Vector2f(toCoordsX(values.x), toCoordsY(values.y));
}

void Plot::setAxisColor(sf::Color color)
{
	Plotter::setAxisColor(color);
}

void Plot::setBackgroundColor(sf::Color color)
{
	background.setFillColor(color);
}

void Plot::setSize(sf::Vector2f newsize)
{
	background.setSize(newsize);
	frame[4] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black);
	frame[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black);
	frame[1] = sf::Vertex(sf::Vector2f(newsize.x, 0), sf::Color::Black);
	frame[2] = sf::Vertex(sf::Vector2f(newsize.x, newsize.y), sf::Color::Black);
	frame[3] = sf::Vertex(sf::Vector2f(0, newsize.y), sf::Color::Black);
}

sf::Vector2f Plot::getSize() const
{
	return background.getSize();
}

void Plot::recompute()
{
	vscale = sf::Vector2f(
		(vend.x - vbegin.x) / getSize().x,
		(vend.y - vbegin.y) / getSize().y
	);
	axisX.recompute();
	axisY.recompute();
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	target.draw(frame, states);
	target.draw(axisX, states);
	//target.draw(axisY, states);
}
