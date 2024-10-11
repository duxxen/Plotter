#pragma once
#include "common.hpp"

class WindowFrame : public sf::NonCopyable
{
	friend class Plot;
	friend class Plotter;
public:

	WindowFrame(size_t id);
	WindowFrame(size_t id, sf::Vector2f size, float dpi);
	WindowFrame(const WindowFrame&& obj) noexcept;

	bool processEvents();
	void show();

private:

	const size_t		id;
	sf::RenderWindow	window;
	sf::Vector2f		size	{ 4.f, 3.f };
	float				dpi		{ 100.f };
	PlotPointer			plot	{ nullptr };
};