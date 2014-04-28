#include "globals.h"

Globals &Globals::getInstance()
{
    static Globals gloInstance;
    return gloInstance;
}

Globals::Globals()
{
    m_rqcColors[0] = QColor(Qt::black);
    m_rqcColors[1] = QColor(Qt::yellow);
    m_rqcColors[2] = QColor(Qt::blue);
    m_rqcColors[3] = QColor(Qt::red);
    m_rqstStateNames[0] = "Leer";
    m_rqstStateNames[1] = "Leiter";
    m_rqstStateNames[2] = "Elektronen-Kopf";
    m_rqstStateNames[3] = "Elektronen-Ende";
    m_dCellHeight = m_dCellWidth = 32;
    m_iX = m_iY = 0;
    m_dZoomFactor = 1;
}

Globals::Globals(Globals &p_gloRef)
{

}

Globals::~Globals()
{

}

Globals &Globals::operator=(Globals &p_gloRef)
{

}
