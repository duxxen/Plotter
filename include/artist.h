#pragma once
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "mathex.hpp"

class Graph;

enum class LineStyle
{
	Solid,
	Dashed,
	Dotted,
	DashDot
};

class Artist
{
public:
	virtual ~Artist() = default;
	virtual void draw(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	) = 0;
};

class LineArtist : public Artist
{
public:
	LineArtist(LineStyle style, float lineThickness);
	void draw(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	) override;

	float getLineThickness() const;
	void setLineThickness(float lineThickness);

private:
	LineStyle lineStyle;
	float lineThickness;

	void drawSolid(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	);
	void drawDashed(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	);
	void drawDotted(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	);
	void drawDashDot(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	);

	void appendPatternSegment(
		const Graph& graph, sf::VertexArray& line,
		float xbeg, float xend, float ybeg, float yend,
		const sf::Color& color, float dashLength, float spacing
	);
	void appendThickSegment(
		const Graph& graph, sf::VertexArray& line,
		float xbeg, float xend, float ybeg, float yend,
		const sf::Color& color
	);
};

class BarArtist : public Artist
{
public:
	BarArtist(float barWidth);;
	void draw(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	) override;

	float getBarWidth() const;
	void setBarWidth(float barWidth);

private:
	float barWidth;
};

class ScatterArtist : public Artist
{
public:
	ScatterArtist(float dotRadius);
	void draw(
		sf::RenderWindow& window,
		const Graph& graph,
		const std::vector<float>& valuesX,
		const std::vector<float>& valuesY,
		const sf::Color& color
	) override;

	float getDotRadius() const;
	void setDotRadius(float dotRadius);

private:
	float dotRadius;
};