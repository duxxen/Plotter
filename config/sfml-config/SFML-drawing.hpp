#pragma once
#include "SFML-config.hpp"
#include "../../main/plot.h"

namespace Plotter
{
	class Engine
	{
		friend void init(Plot* plot);
		friend void shutdown(Plot* plot);
		friend void shutdown();

		friend void proccessEvents();
		friend void update();
		friend void render();

		static inline std::map<Plot*, sf::RenderWindow*> plots;
		static inline sf::Font							 font;
	};

	void init(Plot* plot) {
		auto& style = plot->style;
		auto& window = new sf::RenderWindow(sf::VideoMode(style.size.x, style.size.y), style.name);
		window->setMouseCursorVisible(false);
		Engine::plots[plot] = window;
		Engine::font.loadFromFile(plot->titles.style.fontPath);
	}

	void shutdown(Plot* plot)
	{
		auto iter = Engine::plots.find(plot);
		delete iter->second;
		Engine::plots.erase(iter);
	}

	void shutdown()
	{
		for (auto& node : Engine::plots)
			shutdown(node.first);
	}

	void proccessEvents()
	{
		for (auto& node : Engine::plots)
		{
			auto& plot	= *node.first;
			auto& window = *node.second;

			sf::Event event;
			sf::Vector2i mousePixels;
			sf::Vector2f mouseCoords;

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					shutdown(&plot);
					break;

				case sf::Event::MouseMoved:
					mousePixels = sf::Mouse::getPosition(window);
					mouseCoords = window.mapPixelToCoords(mousePixels);
					plot.onMouseMoved(mouseCoords.x, mouseCoords.y);
					break;

				case sf::Event::MouseButtonPressed:
					plot.onMousePressed(mouseTranslation.at(event.mouseButton.button));
					break;

				case sf::Event::MouseButtonReleased:
					plot.onMouseReleased(mouseTranslation.at(event.mouseButton.button));
					break;

				case sf::Event::KeyPressed:
					plot.onKeyPressed(keyTranslation.at(event.key.code));
					break;

				case sf::Event::KeyReleased:
					plot.onKeyReleased(keyTranslation.at(event.key.code));
					break;

				default:
					break;
				}
			}
		}
	}
	void update()
	{
	}

	void render()
	{
		for (auto& node : Engine::plots)
		{
			auto& plot = *node.first;
			auto& window = *node.second;

			if (plot.style.show & PlotStyle::SHOW_GRID)
			{
				window.draw(toVertexArray(plot.grid.linesV));
				window.draw(toVertexArray(plot.grid.linesH));
			}

			for (auto& graph : plot.graphs)
			{
				if (graph.style.show & GraphStyle::SHOW_LINE)
					window.draw(toVertexArray(graph.gLines));
				if (graph.style.show & GraphStyle::SHOW_VOLUME)
					window.draw(toVertexArray(graph.vTriangles));
			}

			if (plot.style.show & PlotStyle::SHOW_CURSOR)
			{
				window.draw(toVertexArray(plot.mCursor.lines));

				sf::Text text(plot.titles.valuesC[MOUSE_CURSOR].string, Engine::font, plot.titles.style.charSize);
				text.setFillColor(toSfColor(plot.titles.style.color));
				text.setPosition(toVector2<float>(plot.titles.valuesC[MOUSE_CURSOR].position));
				window.draw(text);
			}

			if (plot.style.show & PlotStyle::SHOW_AXIS)
			{
				window.draw(toVertexArray(plot.axis.lines));

				sf::Text text("", Engine::font, plot.titles.style.charSize);
				text.setFillColor(toSfColor(plot.titles.style.color));
				
				for (auto& value : plot.titles.valuesX)
				{
					text.setString(value.string);
					text.setPosition(toVector2<float>(value.position));
					window.draw(text);
				}

				for (auto& value : plot.titles.valuesY)
				{
					text.setString(value.string);
					text.setPosition(toVector2<float>(value.position));
					window.draw(text);
				}
			}
		}
	}
}