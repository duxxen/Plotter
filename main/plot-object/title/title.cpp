#include "title.h"
#include "../../plot.h"

namespace Plotter
{
    Title::Title(Plot* layout, TextStyle style) :
        PlotObject  { layout },
        style       { style }
    {
    }

    void Title::recompute()
    {
        font.loadFromFile(style.fontPath);
    }

    void Title::onStyleChanged()
    {
        recompute();
    }
}