#include "../include/system/label.h"

sf::Font			Label::globalFont;
std::vector<Label*> Label::globalLabels;

Label::Label(const sf::String& string, unsigned characterSize) :
	Text(string, globalFont, characterSize)
{
	if (globalLabels.empty())
	{
		globalFont.loadFromFile(DEFAULT_FONTS_FOLDER + DEFAULT_FONT_NAME);
		Text::setFont(globalFont);
	}
	globalLabels.push_back(this);
}

void Label::setString(int value)
{
	char buf[256];
	sprintf_s(buf, 256, "%d", value);
	Text::setString(buf);
}

void Label::setString(float value)
{
	char buf[256];
	sprintf_s(buf, 256, "%.2f", value);
	Text::setString(buf);
}

void Label::setString(sf::Vector2f vector)
{
	char buf[256];
	sprintf_s(buf, 256, "{ %.2f, %.2f }", vector.x, vector.y);
	Text::setString(buf);
}

void Label::setString(const sf::String& string)
{
	Text::setString(string);
}

void Label::loadGlobalFont(const std::string& path)
{
	globalFont.loadFromFile(path);
	for (auto label : globalLabels)
		label->setFont(globalFont);
}
