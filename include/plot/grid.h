#pragma once
#include "../common.hpp"

class Grid :
	public PlotObject
{
public:
	Grid(Plot* layout, size_t gridCountX, size_t gridCountY);

	void setColor(sf::Color color);
	void setCountX(size_t count);
	void setCountY(size_t count);

private:

	void recomputeX();
	void recomputeY();
	void recompute() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray gridX;
	sf::VertexArray gridY;
};