#pragma once
#include "../object.hpp"
#include "../title/title.h"

namespace Plotter
{
	class Cursor : Object
	{
		friend class Plot;

	public:

		static inline const struct CursorStyle : Style
		{
			enum Flags
			{
				SHOW_NONE = 0,
				SHOW_LINES = 1,
				SHOW_TITLE = SHOW_LINES << 1,
				SHOW_ALL = SHOW_LINES | SHOW_TITLE
			};

			Color	color;
			Flags	flags;
			Coords	titleOffset;
			
			CursorStyle(
				Color color = Color(0x808080ff),
				Flags flags = SHOW_ALL,
				Coords titleOffset = Coords(0, 0)
			);
		}
		DEFAULT_CURSOR_STYLE;

	private:

		Cursor(Plot* layout, CursorStyle style = DEFAULT_CURSOR_STYLE, Title::TitleStyle tstyle = Title::DEFAULT_TITLE_STYLE);

		void setPosition(Coords coords);
		void onStyleChanged(CursorStyle nstyle);
		void onStyleChanged(Title::TitleStyle nstyle);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void init() override;
		void recompute() override;

		CursorStyle		style;

		Title			titleValues;
		sf::VertexArray lines;
	};
}