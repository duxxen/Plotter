#pragma once
#include "../../utility/inputs.hpp"

namespace Plotter
{
	static inline class PlotFunction
	{
	public:
		enum Function
		{
			NONE,
			MOVE_LEFT,
			MOVE_RIGHT,
			MOVE_UP,
			MOVE_DOWN,

			FROM_X_LEFT,
			FROM_X_RIGHT,
			TO_X_LEFT,
			TO_X_RIGHT,

			FROM_Y_UP,
			FROM_Y_DOWN,
			TO_Y_UP,
			TO_Y_DOWN,

			GRAPH_NONE,
			GRAPH_1,
			GRAPH_2,
			GRAPH_3,
			GRAPH_4,
			GRAPH_5,
			GRAPH_6,
			GRAPH_7,
			GRAPH_8,
			GRAPH_9,

			SWITCH_LCURSOR,
			SWITCH_RCURSOR
		};

		PlotFunction()
		{
			keyFunctions.insert(std::make_pair(Keyboard::LEFT, MOVE_LEFT));		// basic
			keyFunctions.insert(std::make_pair(Keyboard::LEFT, FROM_X_LEFT));	// ctrl
			keyFunctions.insert(std::make_pair(Keyboard::LEFT, TO_X_LEFT));		// alt

			keyFunctions.insert(std::make_pair(Keyboard::RIGHT, MOVE_RIGHT));
			keyFunctions.insert(std::make_pair(Keyboard::RIGHT, FROM_X_RIGHT));
			keyFunctions.insert(std::make_pair(Keyboard::RIGHT, TO_X_RIGHT));

			keyFunctions.insert(std::make_pair(Keyboard::UP, MOVE_UP));
			keyFunctions.insert(std::make_pair(Keyboard::UP, FROM_Y_UP));
			keyFunctions.insert(std::make_pair(Keyboard::UP, TO_Y_UP));

			keyFunctions.insert(std::make_pair(Keyboard::DOWN, MOVE_DOWN));
			keyFunctions.insert(std::make_pair(Keyboard::DOWN, FROM_Y_DOWN));
			keyFunctions.insert(std::make_pair(Keyboard::DOWN, TO_Y_DOWN));

			keyFunctions.insert(std::make_pair(Keyboard::NUM_0, GRAPH_NONE));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_1, GRAPH_1));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_2, GRAPH_2));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_3, GRAPH_3));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_4, GRAPH_4));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_5, GRAPH_5));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_6, GRAPH_6));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_7, GRAPH_7));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_8, GRAPH_8));
			keyFunctions.insert(std::make_pair(Keyboard::NUM_9, GRAPH_9));

			keyFunctions.insert(std::make_pair(Keyboard::L, SWITCH_LCURSOR));
			keyFunctions.insert(std::make_pair(Keyboard::R, SWITCH_RCURSOR));
		}

		Function get(Keyboard key)
		{
			auto found = keyFunctions.find(key.code);
			if (found == keyFunctions.end())
				return Function::NONE;

			auto range = keyFunctions.equal_range(key.code);
			auto iter = range.first;
			size_t i = 0;
			if (key.control)	i = 1;
			else if (key.alt)	i = 2;

			for (; iter != range.second && i; iter++)
				i--;

			return iter->second;
		}

		Function get(Mouse mouse)
		{
			auto found = mouseFunctions.find(mouse.button);
			if (found == mouseFunctions.end())
				return Function::NONE;
		}

	private:

		std::multimap<Keyboard::Key, Function> keyFunctions;
		std::multimap<Mouse::Button, Function> mouseFunctions;
	} PLOT_FUNCTIONS;
}