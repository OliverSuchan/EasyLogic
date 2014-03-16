#ifndef GLOBALS_H
#define GLOBALS_H

#include <QColor>

namespace Globals
{

    static qreal CELL_WIDTH = 32;
    static qreal CELL_HEIGHT = 32;
    static qreal ZoomFactor_X = 1.0;
    static qreal ZoomFactor_Y = 1.0;


    enum State {
        EMPTY, CONDUCTOR, HEAD, TAIL
    };

    static const QColor s_rqcColors[] = { QColor(Qt::black), QColor(Qt::yellow), QColor(Qt::blue), QColor(Qt::red) };
}

#endif // GLOBALS_H
