#ifndef GLOBALS_H
#define GLOBALS_H

#include <QColor>

class Globals
{
public:
    enum State {
        EMPTY, CONDUCTOR, HEAD, TAIL
    };

    static Globals &getInstance();
    qreal CELL_WIDTH;
    qreal CELL_HEIGHT;
    qreal ZoomFactor;

    QString m_rqstStateNames[4];
    QColor m_rqcColors[4];

private:
    Globals();
    Globals(Globals &p_gloRef);
    ~Globals();
    Globals &operator=(Globals &p_gloRef);
};

#endif // GLOBALS_H
