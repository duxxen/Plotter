#include "title.h"
#include "plot.h"

namespace Plotter
{
    Title::Title(Plot* layout) :
        PlotObject{ layout },
        style{ TSTYLE_PRESETS[STYLE_DEFAULT] }
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