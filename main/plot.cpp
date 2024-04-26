#include "plot.h"

namespace Plotter
{

    Plot::Plot(std::string name, PlotStyle pStyle, GridStyle gStyle, AxisStyle aStyle, TextStyle tStyle, CursorStyle cStyle) :
        style{ pStyle },
        grid{ this, gStyle },
        axis{ this, aStyle },
        title{ this, tStyle },
        cursor{ this, cStyle }
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
        title.recompute();
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

    void Plot::setStyle(PlotStyle style)
    {
        if (style.indent != this->style.indent ||
            style.size != this->style.size)
        {
            this->style = style;
            recompute();
            return;
        }

        if (style.pointCount != this->style.pointCount)
        {
            this->style = style;
            rebuild();
            recompute();
        }

        if (style.name != this->style.name)
            window.setTitle(style.name);

        this->style = style;
    }

    void Plot::setStyle(size_t index, LineStyle style)
    {
        if (index >= graphs.size())
            throw PlotErrors::INVALID_INDEX;

        graphs[index].style = style;
        graphs[index].onStyleChanged();
    }

    void Plot::setStyle(GridStyle style)
    {
        grid.style = style;
        grid.onStyleChanged();
    }

    void Plot::setStyle(AxisStyle style)
    {
        axis.style = style;
        axis.onStyleChanged();
    }

    void Plot::setStyle(TextStyle style)
    {
        title.style = style;
        title.onStyleChanged();
    }

    void Plot::setStyle(CursorStyle style)
    {
        cursor.style = style;
        cursor.onStyleChanged();
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
            auto endY = std::max(vEnd.y, graphs[index].max.y);

            if (startY != vStart.y || endY != vEnd.y)
            {
                setBoundariesY(startY, endY);
                vAuto = true;
                return;
            }
        }
           
        graphs[index].recompute();
    }

    void Plot::plot(vector<Vec2> points)
    {
        auto graphi = graphs.size();
        graphs.push_back(Graph(this));
        auto stylei = graphi % (sizeof(LSTYLE_PRESETS) / sizeof(LSTYLE_PRESETS[0]));

        plot(graphi, points, LSTYLE_PRESETS[stylei]);
    }

    void Plot::plot(size_t index, vector<Vec2> points)
    {
        auto stylei = index % (sizeof(LSTYLE_PRESETS) / sizeof(LSTYLE_PRESETS[0]));

        plot(index, points, LSTYLE_PRESETS[stylei]);
    }

    void Plot::plot(vector<Vec2> points, LineStyle style)
    {
        auto index = graphs.size();
        graphs.push_back(Graph(this));

        plot(index, points, style);
    }

    void Plot::plot(size_t index, vector<Vec2> points, LineStyle style)
    {
       if (index >= graphs.size())
           throw PlotErrors::INVALID_INDEX;

       graphs[index].graph(points);
       graphs[index].style = style;

       if (vAuto)
       {
           auto startY = std::min(vStart.y, graphs[index].min.y);
           auto endY = std::max(vEnd.y, graphs[index].max.y);

           if (startY != vStart.y || endY != vEnd.y)
           {
               setBoundariesY(startY, endY);
               vAuto = true;
               return;
           }
       }

       graphs[index].recompute();
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
            (cx - bounds.left) / vScale.x + vStart.x,
            -(cy - bounds.top - bounds.height) / vScale.y + vStart.y
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
            graph.graph(graph.func, vStart.x, vEnd.x);
    }

    void Plot::recompute()
    {
        for (auto& graph : graphs)
            graph.recompute();

        grid.recompute();
        axis.recompute();
    }

    void Plot::onMouseMoved()
    {
        cursor.recompute();
    }

    void Plot::onMousePressed()
    {
        mouse.pressed = true;
        
    }

    void Plot::onMouseReleased()
    {
        mouse.pressed = false;
    }

    void Plot::onKeyPressed()
    {
        key.pressed = true;
        switch (key.code)
        {
        case Keyboard::LSHIFT:
        case Keyboard::RSHIFT:  
            key.shift = true;   
            break;

        case Keyboard::LALT:
        case Keyboard::RALT:   
            key.alt = true;     
            break;
            
        case Keyboard::LCTRL:
        case Keyboard::RCTRL:
            key.control = true;
            break;
            
        default:
            break;
        }
    }

    void Plot::onKeyReleased()
    {
        key.pressed = false;
        switch (key.code)
        {
        case Keyboard::LSHIFT:
        case Keyboard::RSHIFT:
            key.shift = false;
            break;

        case Keyboard::LALT:
        case Keyboard::RALT:
            key.alt = false;
            break;

        case Keyboard::LCTRL:
        case Keyboard::RCTRL:
            key.control = false;
            break;

        default:
            break;
        }
    }

    void Plot::initWindow()
    {
        window.create(sf::VideoMode(style.size.x, style.size.y), style.name);
        window.setMouseCursorVisible(false);
    }

    void Plot::updateMouse()
    {
        
    }

    void Plot::pollEvent()
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            Vec2 mouseMoved;

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseMoved:
                mouseMoved = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                mouse.x = mouseMoved.x;
                mouse.y = mouseMoved.y;

                onMouseMoved();
                break;

            case sf::Event::MouseButtonPressed:
                mouse.button = mouseTranslation[event.mouseButton.button];
                onMousePressed();
                break;

            case sf::Event::MouseButtonReleased:
                mouse.button = mouseTranslation[event.mouseButton.button];
                onMouseReleased();
                break;

            case sf::Event::KeyPressed:
                key.code = keyTranslation[event.key.code];
                onKeyPressed();
                break;

            case sf::Event::KeyReleased:
                key.code = keyTranslation[event.key.code];
                onKeyReleased();
                break;

            default:
                break;
            }
            
        }
    }

    void Plot::render()
    {
        window.clear(style.color);

        if (style.show & PlotStyle::SHOW_GRID)
        {
            window.draw(grid.linesV);
            window.draw(grid.linesH);
        }

        for (auto& graph : graphs)
        {
            if (graph.style.show & LineStyle::SHOW_LINE)
                window.draw(graph.gLines);

            if (graph.style.show & LineStyle::SHOW_VOLUME)
                window.draw(graph.vTriangles);
        }

        if (style.show & PlotStyle::SHOW_CURSOR)
        {
            window.draw(cursor.lines);

            sf::Text text("", title.font, title.style.charSize);
            text.setFillColor(title.style.color);
            text.setString(title.valuesC.value);
            text.setPosition(title.valuesC.coords);
            window.draw(text);
        }

        if (style.show & PlotStyle::SHOW_AXIS)
        {
            window.draw(axis.aLines);

            sf::Text text("", title.font, title.style.charSize);
            text.setFillColor(title.style.color);
            for (auto& value : title.valuesX)
            {
                text.setString(value.value);
                text.setPosition(value.coords);
                window.draw(text);
            }
            for (auto& value : title.valuesY)
            {
                text.setString(value.value);
                text.setPosition(value.coords);
                window.draw(text);
            }
        }
        

        window.display();
    }

    

    

}