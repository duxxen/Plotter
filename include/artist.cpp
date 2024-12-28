#include "artist.h"
#include "graph.h"

void LineArtist::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    sf::VertexArray line(sf::LineStrip, valuesX.size());
    for (size_t i = 0; i < valuesX.size(); i++) {
        line[i].position = graph.toPixels(valuesX[i], valuesY[i]);
        line[i].color = color;
    }
    window.draw(line);
}
