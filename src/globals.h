#ifndef GLOBALS_H
#define GLOBALS_H

#include <QColor>

namespace Globals
{
    enum State {
        EMPTY, CONDUCTOR, HEAD, TAIL
    };

    static const QColor s_rqcColors[] = { QColor(Qt::black), QColor(Qt::yellow), QColor(Qt::blue), QColor(Qt::red) };
}

#endif // GLOBALS_H
