#include "plot.h"

namespace Plotter
{
    Plot::Plot(std::string name, PlotStyle pStyle, GridStyle gStyle, AxisStyle aStyle, TextStyle tStyle, CursorStyle cStyle) :
        style{ pStyle },
        grid{ this, gStyle },
        axis{ this, aStyle },
        titles{ this, tStyle },
        lCursor{ this, cStyle },
        rCursor{ this, cStyle },
        mCursor{ this, cStyle }
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
    }

    void Plot::setBoundariesX(float from, float to)
    {
        start.x = from;
        end.x = to;

        rebuild();
        recompute();
    }

    Coords Plot::toCoords(float vx, float vy) const
    {
        return Coords(vx * scale.x, vy * scale.y);
    }

    Coords Plot::toCoords(Values v) const
    {
        return toCoords(v.x, v.y);
    }

    Coords Plot::toCoordsRanged(float vx, float vy) const
    {

    }
}