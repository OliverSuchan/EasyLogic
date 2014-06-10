#ifndef GLOBALS_H
#define GLOBALS_H

#include <QColor>

class Globals
{
    enum State {
        EMPTY, CONDUCTOR, HEAD, TAIL
    };

    static Globals &getInstance();
    int m_dCellWidth;
    int m_dCellHeight;
    int m_iX;
    int m_iY;
    double m_dZoomFactor;

    QString m_rqstStateNames[4];
    QColor m_rqcColors[4];


private:
    Globals();
    Globals(Globals &p_gloRef);
    ~Globals();
    Globals &operator=(Globals &p_gloRef);
};

#endif // GLOBALS_H
