#pragma once
#include <SFML/System.hpp>
#include <cmath>

namespace sf
{
	static float abs(const Vector2f& vec) {
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	static float distance(const Vector2f& vec1, const Vector2f& vec2) {
		return abs(vec2 - vec1);
	}

	static Vector2f normalize(const Vector2f& vec) {
		return vec / abs(vec);
	}
}
