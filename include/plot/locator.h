#pragma once
#include "../common.hpp"

class Locator :
	public PlotObject
{
	friend class Plotter;
public:
	Locator(Orientation orientation, size_t majorCount = 3, size_t minorCount = 2);

	void setColor(sf::Color color);
	void setMajorCount(size_t count);
	void setMinorCount(size_t count);

	size_t getMajorCount() const;
	size_t getMinorCount() const;

	void recomputeMajores();
	void recomputeMinores();
	void recompute() override;

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Orientation			orientation;
	bool				gridEnable;
	sf::VertexArray		grid;
	size_t				majorCount;
	size_t				minorCount;
	sf::VertexArray		majores;
	sf::VertexArray		minores;
	std::vector<Label>	majorLabels;
	std::vector<Label>	minorLabels;
};