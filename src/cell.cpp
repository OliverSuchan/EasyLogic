#include "cell.h"

Cell::Cell() : m_sCellState(Globals::EMPTY)
{
}

Cell::Cell(Globals::State p_sState) : m_sCellState(p_sState)
{
}

void Cell::nextState(){
    if(m_sCellState)
    {
        m_sCellState = static_cast<Globals::State>(m_sCellState + 1);
        if(m_sCellState > 3)
            m_sCellState = Globals::CONDUCTOR;
    }
}
const Globals::State Cell::getState() const{
    return m_sCellState;
}

void Cell::setState(Globals::State p_sValue)
{
    m_sCellState = p_sValue;
}
