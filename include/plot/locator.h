#pragma once
#include "axis.h"

class Locator :
	public PlotObject
{
public:
	Locator(Axis* layout, size_t majorCount = 5, size_t minorCount = 0);

	void setMajorCount(size_t count);
	void setMinorCount(size_t count);

private:

	void recomputeMajores();
	void recomputeMinores();
	void recompute() override;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	size_t				majorCount;
	size_t				minorCount;
	sf::VertexArray		majores;
	sf::VertexArray		minores;
	std::vector<Label>	majorLabels;
	std::vector<Label>	minorLabels;
};