#pragma once
#include "../common.hpp"

namespace Plotter
{
	class Plot;
	class Axis;
	class Grid;
	class Graph;
	class Cursor;
	class Title;

	class Style
	{

	};

	class Object : protected sf::Drawable, protected sf::Transformable
	{
	protected:

		Plot* layout;
		Object(Plot* layout) : layout{ layout } {}

	private:

		virtual void onStyleChanged() = 0;
		virtual void recompute() = 0;
	};
}