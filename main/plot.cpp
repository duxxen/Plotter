#include "plot.h"

namespace Plotter
{
    Plot::Plot(std::string name, PlotStyle pStyle, GridStyle gStyle, AxisStyle aStyle, TextStyle tStyle, CursorStyle cStyle) :
        style{ pStyle },
        grid{ this, gStyle },
        axis{ this, aStyle },
        titles{ this, tStyle }
    {
        style.name = name;

        bounds.left = style.indent.x;
        bounds.top = style.indent.y;
        bounds.width = style.size.x - 2 * style.indent.x;
        bounds.height = style.size.y - 2 * style.indent.y;

        yAuto = true;
        start.x = -10;
        end.x = 10;
        scale.x = bounds.width / (end.x - start.x);

        cursores.push_back(Cursor(this, cStyle));
        for (int i = LEFT_CURSOR; i <= RIGHT_CURSOR; i++)
            cursores.push_back(Cursor(this, CursorStyle(cStyle.color, CursorStyle::SHOW_NONE)));
    }

    void Plot::setBoundariesX(float from, float to)
    {
        start.x = from;
        end.x = to;
        scale.x = bounds.width / (to - from);

        rebuild();
        recompute();
    }

    void Plot::setBoundariesY(float from, float to)
    {
        start.y = from;
        end.y = to;
        yAuto = false;
        scale.y = bounds.height / (to - from);

        recompute();
    }

    void Plot::setBoundaries(float fromX, float toX, float fromY, float toY)
    {
        start.x = fromX;
        start.y = fromY;
        end.x = toX;
        end.y = toY;

        scale.x = bounds.width / (toX - fromX);
        scale.y = bounds.height / (toY - fromY);

        yAuto = false;

        rebuild();
        recompute();
    }

    void Plot::setBoundaries(Vec2 from, Vec2 to)
    {
        setBoundaries(from.x, to.x, from.y, to.y);
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

        /*if (style.name != this->style.name)
            plotTitleChanged();*/

        this->style = style;
    }

    void Plot::setStyle(size_t index, GraphStyle style)
    {
        if (index >= graphs.size())
            throw PlotErrors::INVALID_INDEX;

        graphs[index].style = style;
        graphs[index].onStyleChanged();
    }

    void Plot::setStyle(AxisStyle style)
    {
        axis.style = style;
        axis.onStyleChanged();
    }

    void Plot::setStyle(size_t index, CursorStyle style)
    {
        if (index >= cursores.size())
            throw PlotErrors::INVALID_INDEX;

        cursores[index].style = style;
        cursores[index].onStyleChanged();
    }

    void Plot::setStyle(GridStyle style)
    {
        grid.style = style;
        grid.onStyleChanged();
    }

    void Plot::setStyle(TextStyle style)
    {
        titles.style = style;
        titles.onStyleChanged();
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

    void Plot::plot(Func func, GraphStyle style)
    {
        auto index = graphs.size();
        graphs.push_back(Graph(this));

        plot(index, func, style);
    }

    void Plot::plot(size_t index, Func func, GraphStyle style)
    {
        if (index >= graphs.size())
            throw PlotErrors::INVALID_INDEX;

        graphs[index].graph(func, start.x, end.x);
        graphs[index].style = style;

        if (yAuto)
        {
            auto startY = std::min(start.y, graphs[index].min.y);
            auto endY = std::max(end.y, graphs[index].max.y);

            if (startY != start.y || endY != end.y)
            {
                setBoundariesY(startY, endY);
                yAuto = true;
                return;
            }
        }

        graphs[index].recompute();
    }

    void Plot::plot(vector<Values> points)
    {
        auto graphi = graphs.size();
        graphs.push_back(Graph(this));
        auto stylei = graphi % (sizeof(LSTYLE_PRESETS) / sizeof(LSTYLE_PRESETS[0]));

        plot(graphi, points, LSTYLE_PRESETS[stylei]);
    }

    void Plot::plot(size_t index, vector<Values> points)
    {
        auto stylei = index % (sizeof(LSTYLE_PRESETS) / sizeof(LSTYLE_PRESETS[0]));

        plot(index, points, LSTYLE_PRESETS[stylei]);
    }

    void Plot::plot(vector<Values> points, GraphStyle style)
    {
        auto index = graphs.size();
        graphs.push_back(Graph(this));

        plot(index, points, style);
    }

    void Plot::plot(size_t index, vector<Values> points, GraphStyle style)
    {
        if (index >= graphs.size())
            throw PlotErrors::INVALID_INDEX;

        graphs[index].graph(points);
        graphs[index].style = style;

        if (yAuto)
        {
            auto startY = std::min(start.y, graphs[index].min.y);
            auto endY = std::max(end.y, graphs[index].max.y);

            if (startY != start.y || endY != end.y)
            {
                setBoundariesY(startY, endY);
                yAuto = true;
                return;
            }
        }

        graphs[index].recompute();
    }

    Coords Plot::toCoords(float vx, float vy) const
    {
        return Coords(
            (vx - start.x) * scale.x + bounds.left,
            (vy - start.y) * scale.y + bounds.bottom()
        );
    }

    Coords Plot::toCoords(Values v) const
    {
        return toCoords(v.x, v.y);
    }

    Coords Plot::toCoordsRanged(float vx, float vy) const
    {
        return range(toCoords(vx, vy));
    }

    Coords Plot::toCoordsRanged(Values value) const
    {
        return range(toCoords(value));
    }

    Values Plot::toValues(float cx, float cy) const
    {
        return Values(
            (cx - bounds.left) / scale.x + start.x,
            -(cy - bounds.bottom()) / scale.y + start.y
        );
    }

    Values Plot::toValues(Coords coord) const
    {
        return toValues(coord.x, coord.y);
    }

    Coords Plot::range(float cx, float cy) const
    {
        return Coords(
            std::min(std::max(bounds.left, cx), bounds.right()), 
            std::min(std::max(bounds.top, cy), bounds.bottom())
        );
    }

    Coords Plot::range(Coords coord) const
    {
        return range(coord.x, coord.y);
    }

    void Plot::rebuild()
    {
        for (auto& graph : graphs)
            graph.graph(graph.func, start.x, end.x);

        grid.recompute();
        axis.recompute();
    }

    void Plot::recompute()
    {
        for (auto& graph : graphs)
            graph.recompute();

        grid.recompute();
        axis.recompute();
    }

    void Plot::onMouseMoved(float x, float y)
    {
        mouse.x = x;
        mouse.y = y;

        cursores[MOUSE_CURSOR].position = toValues(x, y);
        cursores[MOUSE_CURSOR].recompute();
    }

    void Plot::onMousePressed(Mouse::Button button)
    {
        mouse.pressed = true;
        mouse.button = button;
    }

    void Plot::onMouseReleased(Mouse::Button button)
    {
        mouse.pressed = false;
        mouse.button = button;
    }

    void Plot::onKeyPressed(Keyboard::Key key)
    {
        keyboard.pressed = true;
        keyboard.code = key;
        switch (keyboard.code)
        {
        case Keyboard::LSHIFT:
        case Keyboard::RSHIFT:
            keyboard.shift = true;
            break;

        case Keyboard::LALT:
        case Keyboard::RALT:
            keyboard.alt = true;
            break;

        case Keyboard::LCTRL:
        case Keyboard::RCTRL:
            keyboard.control = true;
            break;

        default:
            break;
        }
    }
    void Plot::onKeyReleased(Keyboard::Key key)
    {
        keyboard.pressed = true;
        keyboard.code = key;
        switch (keyboard.code)
        {
        case Keyboard::LSHIFT:
        case Keyboard::RSHIFT:
            keyboard.shift = false;
            break;

        case Keyboard::LALT:
        case Keyboard::RALT:
            keyboard.alt = false;
            break;

        case Keyboard::LCTRL:
        case Keyboard::RCTRL:
            keyboard.control = false;
            break;

        default:
            break;
        }
    }
}