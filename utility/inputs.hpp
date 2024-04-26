#pragma once
#include <SFML/Graphics.hpp>

namespace Plotter
{
	struct Keyboard
	{
		enum Key
		{
			UNKNOWN,
			LEFT, 
			RIGHT,
			UP,
			DOWN,

			LSHIFT,
			RSHIFT,
			LCTRL,
			RCTRL,
			LALT,
			RALT,

			SPACE,
			ESCAPE,
			ENTER,
			TAB,

			NUM_0,
			NUM_1,
			NUM_2,
			NUM_3,
			NUM_4,
			NUM_5,
			NUM_6,
			NUM_7,
			NUM_8,
			NUM_9,

			L,
			R
		};

		Key code;
		bool shift;
		bool control;
		bool alt;
		bool pressed;
	};

	struct Mouse
	{
		enum Button
		{
			LEFT,
			RIGHT,
			MIDDLE
		};

		float x, y;
		Button button;
		bool pressed;
	};

	static inline map<sf::Keyboard::Key, Keyboard::Key>   keyTranslation{
			{ sf::Keyboard::Left,       Keyboard::LEFT },
			{ sf::Keyboard::Right,      Keyboard::RIGHT },
			{ sf::Keyboard::Up,         Keyboard::UP },
			{ sf::Keyboard::Down,       Keyboard::DOWN },

			{ sf::Keyboard::LShift,     Keyboard::LSHIFT },
			{ sf::Keyboard::RShift,     Keyboard::RSHIFT },
			{ sf::Keyboard::LControl,   Keyboard::LCTRL },
			{ sf::Keyboard::RControl,   Keyboard::RCTRL },
			{ sf::Keyboard::LAlt,       Keyboard::LALT },
			{ sf::Keyboard::RAlt,       Keyboard::RALT },

			{ sf::Keyboard::Space,      Keyboard::SPACE },
			{ sf::Keyboard::Enter,      Keyboard::ENTER },
			{ sf::Keyboard::Escape,     Keyboard::ESCAPE },
			{ sf::Keyboard::Tab,        Keyboard::TAB },

			{ sf::Keyboard::Num0,       Keyboard::NUM_0 },
			{ sf::Keyboard::Num1,       Keyboard::NUM_1 },
			{ sf::Keyboard::Num2,       Keyboard::NUM_2 },
			{ sf::Keyboard::Num3,       Keyboard::NUM_3 },
			{ sf::Keyboard::Num4,       Keyboard::NUM_4 },
			{ sf::Keyboard::Num5,       Keyboard::NUM_5 },
			{ sf::Keyboard::Num6,       Keyboard::NUM_6 },
			{ sf::Keyboard::Num7,       Keyboard::NUM_7 },
			{ sf::Keyboard::Num8,       Keyboard::NUM_8 },
			{ sf::Keyboard::Num9,       Keyboard::NUM_9 },

			{ sf::Keyboard::Unknown,    Keyboard::UNKNOWN }
	};

	static inline map<sf::Mouse::Button, Mouse::Button>   mouseTranslation{
		{ sf::Mouse::Left,          Mouse::LEFT },
		{ sf::Mouse::Right,         Mouse::RIGHT },
		{ sf::Mouse::Middle,        Mouse::MIDDLE }
	};
}