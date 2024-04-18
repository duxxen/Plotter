#include "plot.h"

namespace Plotter
{

    Plot::Plot(std::string name, PlotStyle pStyle, GridStyle gStyle, AxisStyle aStyle, TextStyle tStyle) :
        style{ pStyle },
        grid{ this },
        axis{ this },
        titles{ this },
        cursor{ this }
    {
        style.name = name;

        bounds.left = style.indent.x;
        bounds.top = style.indent.y;
        bounds.width = style.size.x - 2 * style.indent.x;
        bounds.height = style.size.y - 2 * style.indent.y;

        vAuto = true;
        vStart.x = -10;
        vEnd.x = 10;
        vScale.x = bounds.width / (vEnd.x - vStart.x);

        initWindow();
        titles.recompute();
    }

    void Plot::setBoundariesX(float startX, float endX)
    {
        vStart.x = startX;
        vEnd.x = endX;
        vScale.x = bounds.width / (endX - startX);

        rebuild();
        recompute();
    }

    void Plot::setBoundariesY(float startY, float endY)
    {
        vStart.y = startY;
        vEnd.y = endY;
        vScale.y = bounds.height / (endY - startY);
        vAuto = false;

        recompute();
    }

    void Plot::setBoundaries(float startX, float endX, float startY, float endY)
    {
        vStart.x = startX;
        vStart.y = startY;
        vEnd.x = endX;
        vEnd.y = endY;

        vScale.x = bounds.width / (endX - startX);
        vScale.y = bounds.height / (endY - startY);

        vAuto = false;

        rebuild();
        recompute();
    }

    void Plot::setBoundaries(Vec2 start, Vec2 end)
    {
        setBoundaries(start.x, end.x, start.y, end.y);
    }

    void Plot::plot(Func func)
    {
        auto graphi = graphs.size();
        graphs.push_back(Graph(this));
        auto stylei = graphi % (sizeof(LSTYLE_PRESETS) / sizeof(LSTYLE_PRESETS[0]));

        plot(graphi, func, LSTYLE_PRESETS[stylei]);
    }

    void Plot::plot(size_t index, Func func)
    {
        auto stylei = index % (sizeof(LSTYLE_PRESETS) / sizeof(LSTYLE_PRESETS[0]));
       
        plot(index, func, LSTYLE_PRESETS[stylei]);
    }

    void Plot::plot(Func func, LineStyle style)
    {
        auto index = graphs.size();
        graphs.push_back(Graph(this));

        plot(index, func, style);
    }

    void Plot::plot(size_t index, Func func, LineStyle style)
    {
        if (index >= graphs.size())
            throw PlotErrors::INVALID_INDEX;

        graphs[index].graph(func, vStart.x, vEnd.x);
        graphs[index].style = style;

        if (vAuto)
        {
            auto startY = std::min(vStart.y, graphs[index].min.y);
            auto endY   = std::max(vEnd.y, graphs[index].max.y);

            if (startY != vStart.y || endY != vEnd.y)
            {
                setBoundariesY(startY, endY);
                vAuto = true;
            }
        }
        else
        {
            graphs[index].recompute();
        }
        
    }

    void Plot::update()
    {
        pollEvent();
        render();
    }

    Vec2 Plot::toCoords(float vx, float vy) const
    {
        return Vec2(
            ((vx - vStart.x) * vScale.x) + bounds.left,
            -((vy - vStart.y) * vScale.y) + bounds.top + bounds.height
        );
    }

    Vec2 Plot::toCoords(Vec2 value) const
    {
        return toCoords(value.x, value.y);
    }

    Vec2 Plot::toCoordsRanged(float vx, float vy) const
    {
        return range(toCoords(vx, vy));
    }

    Vec2 Plot::toCoordsRanged(Vec2 value) const
    {
        return toCoordsRanged(value.x, value.y);
    }

    Vec2 Plot::toValues(float cx, float cy) const
    {
        return Vec2(
            (cx - bounds.left) / vScale.x,
            (cy - bounds.top) / vScale.y
        );
    }

    Vec2 Plot::toValues(Vec2 coord) const
    {
        return toValues(coord.x, coord.y);
    }

    Vec2 Plot::range(float cx, float cy) const
    {
        return Vec2(
            std::min(std::max(cx, bounds.left), bounds.left + bounds.width),
            std::min(std::max(cy, bounds.top), bounds.top + bounds.height)
        );
    }

    Vec2 Plot::range(Vec2 coord) const
    {
        return range(coord.x, coord.y);
    }

    void Plot::rebuild()
    {
        for (auto& graph : graphs)
            graph.graph(graph.func, vStart.x, vStart.y);
    }

    void Plot::recompute()
    {
        for (auto& graph : graphs)
            graph.recompute();

        grid.recompute();
        axis.recompute();
    }

    void Plot::initWindow()
    {
        window.create(sf::VideoMode(style.size.x, style.size.y), style.name);
    }

    void Plot::updateMouse()
    {
        cursor.recompute();
    }

    void Plot::pollEvent()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseMoved:
                mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                updateMouse();
                break;

            default:
                break;
            }
            
        }
    }

    void Plot::render()
    {
        window.clear();

        for (auto& graph : graphs)
        {
            window.draw(graph.gLines);

            if (style.show & PlotStyle::SHOW_VOLUME)
                window.draw(graph.vTriangles);
        }

        if (style.show & PlotStyle::SHOW_GRID)
        {
            window.draw(grid.linesV);
            window.draw(grid.linesH);
        }

        if (style.show & PlotStyle::SHOW_AXIS)
        {
            window.draw(axis.lines);

            sf::Text text("", titles.font, titles.style.charSize);
            for (auto& value : titles.valuesX)
            {
                text.setString(value.value);
                text.setPosition(value.coords);
                window.draw(text);
            }
            for (auto& value : titles.valuesY)
            {
                text.setString(value.value);
                text.setPosition(value.coords);
                window.draw(text);
            }
        }

        if (style.show & PlotStyle::SHOW_CURSOR)
        {
            window.draw(cursor.lines);

            sf::Text text("", titles.font, titles.style.charSize);
            text.setString(titles.valuesC.value);
            text.setPosition(titles.valuesC.coords);
        }

        

        window.display();
    }

    

    

}