#pragma once
#include <SFML/Graphics.hpp>
#include "../../system/system.hpp"

namespace Plotter
{
	inline static const std::map<sf::Keyboard::Key, System::Keyboard::Key>	keyTranslation{
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

	inline static const std::map<sf::Mouse::Button, System::Mouse::Button>	mouseTranslation{
			{ sf::Mouse::Left,          Mouse::LEFT },
			{ sf::Mouse::Right,         Mouse::RIGHT },
			{ sf::Mouse::Middle,        Mouse::MIDDLE }
	};

	inline static const std::map<System::PrimitiveType, sf::PrimitiveType>	primitiveTranslation{
			{ System::PrimitiveType::Points,		sf::PrimitiveType::Points },
			{ System::PrimitiveType::Lines,			sf::PrimitiveType::Lines },
			{ System::PrimitiveType::LineStrip,		sf::PrimitiveType::LineStrip },
			{ System::PrimitiveType::TriangleStrip, sf::PrimitiveType::TriangleStrip },
	};

	template <typename T>
	Vec2 toVec2(const sf::Vector2<T>& v) {
		return Vec2(v.x, v.y);
	}

	template <typename T>
	sf::Vector2<T> toVector2(const Vec2& v) {
		return sf::Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
	}

	Color toColor(const sf::Color& c) {
		return Color(c.r, c.g, c.b, c.a);
	}

	sf::Color toSfColor(const Color& c) {
		return sf::Color(c.r, c.g, c.b, c.a);
	}

	Vertex toVertex(const sf::Vertex& v) {
		return Vertex(toVec2(v.position), toColor(v.color));
	}

	sf::Vertex toSfVertex(const Vertex& v) {
		return sf::Vertex(toVector2<float>(v.position), toSfColor(v.color));
	}

	PrimitiveType toPrimitiveType(sf::PrimitiveType type) {
		for (auto& node : primitiveTranslation)
			if (node.second == type)
				return node.first;
	}

	sf::PrimitiveType toSfPrimitiveType(PrimitiveType type) {
		return primitiveTranslation.at(type);
	}

	Vertices toVertices(const sf::VertexArray& v) {
		Vertices w{ toPrimitiveType(v.getPrimitiveType()), v.getVertexCount() };
		for (auto i = 0; i < w.getSize(); i++)
			w[i] = toVertex(v[i]);

		return w;
	}

	sf::VertexArray toVertexArray(const Vertices& v) {
		sf::VertexArray w{ toSfPrimitiveType(v.getType()), v.getSize() };
		for (auto i = 0; i < v.getSize(); i++)
			w[i] = toSfVertex(v[i]);

		return w;
	}
}