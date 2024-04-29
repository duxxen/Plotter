#include "titles.h"
#include "../../plot.h"

namespace Plotter
{
    Titles::Titles(Plot* layout, TextStyle style) :
        PlotObject{ layout },
        style{ style }
    {
    }

    void Titles::recompute()
    {

    }

    void Titles::onStyleChanged()
    {
        recompute();
    }
}