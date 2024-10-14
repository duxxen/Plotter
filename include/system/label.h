#pragma once
#include <SFML/Graphics.hpp>

static inline const std::string	DEFAULT_FONTS_FOLDER{ "C:/Windows/Fonts/" };
static inline const std::string	DEFAULT_FONT_NAME	{ "arial.ttf" };

class Label :
	public sf::Text
{
public:
	Label(const sf::String& string = "", unsigned characterSize = 30U);

	void setString(int value);
	void setString(float value);
	void setString(sf::Vector2f vector);
	void setString(const sf::String& string);

	static void loadGlobalFont(const std::string& path = "");
	
private:

	static sf::Font				globalFont;
	static std::vector<Label*>	globalLabels;
};