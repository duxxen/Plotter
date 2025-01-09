#include "legend.h"
#include "graph.h"

Legend::Item::Item(const std::string& label, const sf::Color& color) :
	label(label),
	color(color)
{
}

Legend::Legend(const Graph& layout, const sf::Vector2f& pos, const sf::Color& bgColor, const sf::Color& frColor) :
	layout(layout),
	position(pos),
	frameColor(frColor),
	backgroundColor(bgColor)
{
}

void Legend::addItem(const std::string& label, const sf::Color& color)
{
	items.push_back(Item(label, color));
}

void Legend::draw(sf::RenderWindow& window)
{
	float width = 0.0f;
	for (const auto& item : items)
	{
		float twidth = fontSize * item.label.size() * 0.5f;
		width = std::max(width, twidth);
	}
	width += innerPadding * 2 + 30;
	float height = items.size() * (itemHeight + itemSpacing) + innerPadding * 2;

	sf::RectangleShape background({ width, height });
	background.setPosition(position);
	background.setOutlineThickness(-1.0f);
	background.setOutlineColor(frameColor);
	background.setFillColor(backgroundColor);
	window.draw(background);

	sf::RectangleShape itemBox({ 20.0f, itemHeight });
	itemBox.setOutlineThickness(-1.0f);
	itemBox.setOutlineColor(frameColor);

	sf::Text itemText("", layout.getFont(), fontSize);
	itemText.setFillColor(frameColor);

	float currenty = position.y + innerPadding;
	for (const auto& item : items)
	{
		itemBox.setFillColor(item.color);
		itemBox.setPosition(position.x + innerPadding, currenty);
		window.draw(itemBox);

		itemText.setString(item.label);
		itemText.setPosition(position.x + innerPadding + 30, currenty);
		window.draw(itemText);
		currenty += itemHeight + itemSpacing;
	}
}

