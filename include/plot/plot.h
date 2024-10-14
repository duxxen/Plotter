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
	public PlotObject, public sf::Transformable
{
public:
	Plot(
		Window* layout,
		float aleft = DEFAULT_ADJUST_LEFT,
		float atop = DEFAULT_ADJUST_TOP,
		float aright = DEFAULT_ADJUST_RIGHT,
		float abottom = DEFAULT_ADJUST_BOTTOM
	);

	Plot(
		Window* layout,
		sf::Vector2f aposlt = { DEFAULT_ADJUST_LEFT, DEFAULT_ADJUST_TOP },
		sf::Vector2f aposrb = { DEFAULT_ADJUST_RIGHT, DEFAULT_ADJUST_BOTTOM }
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
		sf::Vector2f vbegin = { DEFAULT_VALUES_BEGIN_X, DEFAULT_VALUES_BEGIN_Y },
		sf::Vector2f vend = { DEFAULT_VALUES_END_X, DEFAULT_VALUES_END_Y },
		sf::Vector2f aposlt = { DEFAULT_ADJUST_LEFT, DEFAULT_ADJUST_TOP },
		sf::Vector2f aposrb = { DEFAULT_ADJUST_RIGHT, DEFAULT_ADJUST_BOTTOM }
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

private:

	void recompute() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f		size;
	sf::VertexArray		frame;
	sf::RectangleShape	background;

	sf::Vector2f vbegin;
	sf::Vector2f vend;
	sf::Vector2f vscale;
};