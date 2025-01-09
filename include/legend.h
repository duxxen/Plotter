#pragma once
#include "common.hpp"

class Legend
{
	friend class Graph;
private:
	struct Item
	{
		std::string label;
		sf::Color color;
		Item(const std::string& label, const sf::Color& color);
	};
public:
	Legend(const Graph& layout, const sf::Vector2f& pos, const sf::Color& bgColor, const sf::Color& frColor);

	void addItem(const std::string& label, const sf::Color& color);
	void draw(sf::RenderWindow& window);

private:

	const Graph& layout;

	sf::Vector2f position;
	sf::Color backgroundColor;
	sf::Color frameColor;
	float innerPadding = 10.0f;

	std::vector<Item> items;
	float itemHeight = 10.0f;
	float itemSpacing = 5.0f;
	float fontSize = 12.f;
};