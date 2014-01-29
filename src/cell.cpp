#include "cell.h"

Cell::Cell() : m_sCellState(Globals::EMPTY)
{
}

void Cell::nextState(){
    if(m_sCellState)
    {
        try
        {
            m_sCellState = static_cast<Globals::State>(m_sCellState + 1);
        }
        catch(std::exception)
        {
            m_sCellState = Globals::CONDUCTOR;
        }
    }
}

void Cell::setElectron(){
    m_sCellState = Globals::CONDUCTOR;
}

const Globals::State Cell::getState() const{
    return m_sCellState;
}
