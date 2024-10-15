#pragma once
#include "axis.h"

static inline const float DEFAULT_ADJUST_LEFT	{ .125f };
static inline const float DEFAULT_ADJUST_RIGHT	{ .9f };
static inline const float DEFAULT_ADJUST_TOP	{ .88f };
static inline const float DEFAULT_ADJUST_BOTTOM	{ .1f };

static inline const float DEFAULT_VALUES_BEGIN_X{ 0.f };
static inline const float DEFAULT_VALUES_BEGIN_Y{ 0.f };
static inline const float DEFAULT_VALUES_END_X	{ 1.f };
static inline const float DEFAULT_VALUES_END_Y	{ 1.f };

class Plot :
	public PlotObject
{
	friend class Plotter;
public:

	Plot(
		Window* layout,
		sf::Vector2f aposlt,
		sf::Vector2f aposrb
	);

	Plot(
		Window* layout, 
		float vxbegin = DEFAULT_VALUES_BEGIN_X,
		float vybegin = DEFAULT_VALUES_BEGIN_Y,
		float vxend = DEFAULT_VALUES_END_X,
		float vyend = DEFAULT_VALUES_END_Y,
		float aleft = DEFAULT_ADJUST_LEFT,
		float atop = DEFAULT_ADJUST_TOP,
		float aright = DEFAULT_ADJUST_RIGHT,
		float abottom = DEFAULT_ADJUST_BOTTOM
	);

	Plot(
		Window* layout,
		sf::Vector2f vbegin,
		sf::Vector2f vend,
		sf::Vector2f aposlt,
		sf::Vector2f aposrb
	);

	void adjust(float aleft, float atop, float aright, float abottom);
	void adjust(sf::Vector2f aposlt, sf::Vector2f aposrb);
	void setBounds(float vxbegin, float vybegin, float vxend, float vyend);
	void setBounds(sf::Vector2f vbegin, sf::Vector2f vend);

	float toValuesX(float cx) const;
	float toValuesY(float cy) const;
	sf::Vector2f toValues(sf::Vector2f coords) const;

	float toCoordsX(float vx) const;
	float toCoordsY(float vy) const;
	sf::Vector2f toCoords(sf::Vector2f values) const;

	void setAxisColor(sf::Color color);
	void setBackgroundColor(sf::Color color);

	void setSize(sf::Vector2f newsize);
	sf::Vector2f getSize() const;

	void recompute() override;

	Axis	axisX;
	Axis	axisY;
private:

	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const Window*		layout;
	sf::Vector2f		size;
	sf::VertexArray		frame;
	sf::RectangleShape	background;

	sf::Vector2f		vbegin;
	sf::Vector2f		vend;
	sf::Vector2f		vscale;
};