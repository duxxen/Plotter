#include <SFML/Graphics.hpp>

class Layout
{
public:
	Layout(Layout* layout) : layout(layout) {}
	const Layout* toLayout() { return layout; }
private:
	const Layout* layout;
};

class PlotObject :
	public sf::Drawable, public Layout
{
public:
	PlotObject(Layout* layout) : Layout(layout) {}
private:
	virtual void recompute() = 0;
};