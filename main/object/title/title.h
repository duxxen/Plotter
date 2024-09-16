#pragma once
#include "../object.hpp"

namespace Plotter
{
	class Title : Object
	{
		friend class Plot;
		friend class Grid;
		friend class Cursor;
		
	public:

		static inline const struct TitleStyle : Style
		{
			Color	color;
			uint8_t	charSize;
			string	fontPath;

			TitleStyle(
				Color color = Color::White,
				uint8_t charSize = 10U,
				string fontPath = "assets/arial.ttf"
			);
		}
		DEFAULT_TITLE_STYLE;

	private:

		Title(Plot* layout, TitleStyle style = DEFAULT_TITLE_STYLE);

		void setString(string string);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void onStyleChanged() override;
		void recompute() override;

		TitleStyle style;

		Coords size;

		sf::Font font;
		sf::Text text;
	};
}