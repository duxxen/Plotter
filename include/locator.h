#pragma once
#include "common.h"

class Locator : public sf::Drawable
{
	friend class Plotter;
	friend class Axis;
public:
	Locator(Axis* layout, size_t majorCount = 0, size_t minorCount = 0);

	void setMajorCount(size_t count);
	void setMinorCount(size_t count);

private:

	void recompute();
	void recomputeMajores();
	void recomputeMinores();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const Axis*				layout;
	size_t					majorCount;
	size_t					minorCount;
	sf::VertexArray			majores;
	sf::VertexArray			minores;
	std::vector<sf::Text>	majorLabels;
	std::vector<sf::Text>	minorLabels;
};