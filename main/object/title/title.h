#pragma once
#include "../object.hpp"

namespace Plotter
{
	class Title : Object
	{
		friend class Plot;
		friend class Axis;
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
				uint8_t charSize = 12U,
				string fontPath = "assets/arial.ttf"
			);
		}
		DEFAULT_TITLE_STYLE;

	private:

		Title(Plot* layout, TitleStyle style = DEFAULT_TITLE_STYLE);

		void setString(sf::String string);
		void onStyleChanged(TitleStyle nstyle);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void init() override;
		void recompute() override;

		static sf::Font font;
		static bool		fontLoaded;

		TitleStyle		style;

		Coords			size;
		sf::Text		text;
	};
}