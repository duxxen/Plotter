#include "artist.h"
#include "graph.h"

LineArtist::LineArtist(LineStyle lineStyle, float lineThickness) :
    lineStyle(lineStyle),
    lineThickness(lineThickness)
{
}

void LineArtist::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    if (valuesX.size() < 2 || 
        valuesY.size() < 2) return;

    switch (lineStyle)
    {
    case LineStyle::Solid:
        drawSolid(window, graph, valuesX, valuesY, color);
        break;
    case LineStyle::Dashed:
        drawDashed(window, graph, valuesX, valuesY, color);
        break;
    case LineStyle::Dotted:
        drawDotted(window, graph, valuesX, valuesY, color);
        break;
    case LineStyle::DashDot:
        drawDashDot(window, graph, valuesX, valuesY, color);
        break;
    }
}

float LineArtist::getLineThickness() const
{
    return lineThickness;
}

void LineArtist::setLineThickness(float lineThickness)
{
    this->lineThickness = lineThickness;
}

void LineArtist::drawSolid(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    sf::VertexArray line(sf::TriangleStrip);
    for (size_t i = 0; i < valuesX.size() - 1; i++) 
    {
        appendThickSegment(graph, line, valuesX[i], valuesX[i + 1], valuesY[i], valuesY[i + 1], color);
    }
    window.draw(line);
}

void LineArtist::drawDashed(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    sf::VertexArray line(sf::TriangleStrip);
    float dashlen = 1.0f;
    for (size_t i = 0; i < valuesX.size() - 1; i++) 
    {
        appendPatternSegment(graph, line, valuesX[i], valuesX[i + 1], valuesY[i], valuesY[i + 1], color, dashlen, dashlen);
    }
    window.draw(line);
}

void LineArtist::drawDotted(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    sf::CircleShape dotShape(lineThickness / 2);
    dotShape.setFillColor(color);

    float dotSpacing = 5 * lineThickness;
    for (size_t i = 0; i < valuesX.size() - 1; i++) 
    {
        auto pos1 = graph.toPixels(valuesX[i], valuesY[i]);
        auto pos2 = graph.toPixels(valuesX[i + 1], valuesY[i + 1]);
        auto length = sf::distance(pos1, pos2);
        auto dir = sf::normalize(pos2 - pos1);

        for (float t = 0; t < length; t += dotSpacing) {
            dotShape.setPosition(
                pos1.x + dir.x * t - lineThickness / 2,
                pos1.y + dir.y * t - lineThickness / 2
            );
            window.draw(dotShape);
        }
    }
}

void LineArtist::drawDashDot(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
}

void LineArtist::appendPatternSegment(const Graph& graph, sf::VertexArray& line, float xbeg, float xend, float ybeg, float yend, const sf::Color& color, float dashLength, float spacing)
{
    sf::Vector2f current(xbeg, ybeg);
    sf::Vector2f direction(xend - xbeg, yend - ybeg);
    float segmentLength = sf::abs(direction);
    direction /= segmentLength;

    bool dash = true;
    float remainingLength = segmentLength;
    while (remainingLength > 0)
    {
        float step = dash ? dashLength : spacing;
        step = std::min(step, remainingLength);

        sf::Vector2f next = current + direction * step;
        if (dash) {
            appendThickSegment(graph, line, current.x, next.x, current.y, next.y, color);
        }

        dash = !dash;
        current = next;
        remainingLength -= step;
    }
}

void LineArtist::appendThickSegment(const Graph& graph, sf::VertexArray& line, float xbeg, float xend, float ybeg, float yend, const sf::Color& color)
{
    auto pos1 = graph.toPixels(xbeg, ybeg);
    auto pos2 = graph.toPixels(xend, yend);

    auto dir = pos2 - pos1;
    auto n = sf::normalize({ -dir.y, dir.x }) * (lineThickness / 2.f);

    line.append(sf::Vertex(pos1 + n, color));
    line.append(sf::Vertex(pos1 - n, color));
    line.append(sf::Vertex(pos2 + n, color));
    line.append(sf::Vertex(pos2 - n, color));
}

BarArtist::BarArtist(float barWidth) :
    barWidth(barWidth)
{
}

void BarArtist::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    sf::RectangleShape barShape;
    barShape.setFillColor(color);
    for (size_t i = 0; i < valuesX.size(); i++) {
        auto ltpx = graph.toPixels(valuesX[i] - barWidth / 2.f, valuesY[i]);
        auto rbpx = graph.toPixels(valuesX[i] + barWidth / 2.f, 0);
        barShape.setSize({ rbpx.x - ltpx.x, rbpx.y - ltpx.y });
        barShape.setPosition(ltpx.x, ltpx.y);
        window.draw(barShape);
    }
}

float BarArtist::getBarWidth() const
{
    return barWidth;
}

void BarArtist::setBarWidth(float barWidth)
{
    this->barWidth = barWidth;
}

ScatterArtist::ScatterArtist(float dotRadius) :
    dotRadius(dotRadius)
{
}

void ScatterArtist::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<float>& valuesX, const std::vector<float>& valuesY, const sf::Color& color)
{
    sf::CircleShape dotShape(dotRadius);
    dotShape.setFillColor(color);
    for (size_t i = 0; i < valuesX.size(); i++)
    {
        dotShape.setPosition(graph.toPixels(valuesX[i], valuesY[i]));
        window.draw(dotShape);
    }
}

float ScatterArtist::getDotRadius() const
{
    return dotRadius;
}

void ScatterArtist::setDotRadius(float dotRadius)
{
    this->dotRadius = dotRadius;
}
