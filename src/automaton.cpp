#include "automaton.h"

Automaton::Automaton() : m_lCurrentGen(0)
{
    m_caCells.push_back(std::vector<Cell>());
}

Automaton::Automaton(int p_iHeight, int p_iWidth) : m_lCurrentGen(0)
{
    for(int iAbscissas = 0; iAbscissas < p_iWidth; iAbscissas++)
    {
        m_caCells.push_back(std::vector<Cell>());
        for(int iOrdinants = 0; iOrdinants < p_iHeight; iOrdinants++) m_caCells.at(iAbscissas).push_back(Cell());
    }
}

void Automaton::setCell(Cell p_cValue, int p_iAbscissa, int p_iOrdinant)
{
    m_caCells.at(p_iAbscissa).at(p_iOrdinant) = p_cValue;
}

void Automaton::setCellState(Globals::State p_sValue, int p_iAbscissa, int p_iOrdinant)
{
    Cell cTempCell = m_caCells.at(p_iAbscissa).at(p_iOrdinant);
    cTempCell.setState(p_sValue);
    this->setCell(cTempCell, p_iAbscissa, p_iOrdinant);
}

long Automaton::nextGeneration()
{
    m_caAuxilliaryArray = m_caCells;
    for(int iCounterAbscissas = 0; iCounterAbscissas < m_caAuxilliaryArray.size(); iCounterAbscissas++)
    {
        for(int iCounterOrdinants = 0; iCounterOrdinants < m_caAuxilliaryArray.at(iCounterAbscissas).size(); iCounterOrdinants++)
        {
            Cell cCurrentCell = m_caAuxilliaryArray.at(iCounterAbscissas).at(iCounterOrdinants);
            if(cCurrentCell.getState() == Globals::CONDUCTOR)
            {
                if(checkCell(iCounterAbscissas, iCounterOrdinants))
                {
                    cCurrentCell.nextState();
                }
            }
            else cCurrentCell.nextState();
            m_caCells.at(iCounterAbscissas).at(iCounterOrdinants) = cCurrentCell;
        }
    }
    return ++m_lCurrentGen;
}

const Globals::State Automaton::getStateAt(int p_iX, int p_iY) const
{
    return m_caCells.at(p_iX).at(p_iY).getState();
}

int Automaton::getWidth() const
{
    return m_caCells.size();
}

int Automaton::getHeight() const
{
    return m_caCells.at(0).size();
}

bool Automaton::checkCell(int p_iAbscissa, int p_iOrdinant)
{
    short sElectronCounter = 0;
    for(int iCounterAbscissas = p_iAbscissa - 1; iCounterAbscissas <= p_iAbscissa + 1; iCounterAbscissas++)
    {
        for(int iCounterOrdinants = p_iOrdinant - 1; iCounterOrdinants <= p_iOrdinant + 1; iCounterOrdinants++)
        {
            if(iCounterAbscissas >= 0 && iCounterAbscissas < this->m_caAuxilliaryArray.size() && iCounterOrdinants >= 0 && iCounterOrdinants < this->m_caAuxilliaryArray.at(iCounterAbscissas).size())
            {
                if(m_caAuxilliaryArray.at(iCounterAbscissas).at(iCounterOrdinants).getState() == Globals::HEAD)
                {
                    ++sElectronCounter;
                }
            }
        }
    }
    if(sElectronCounter >= 1 && sElectronCounter <= 2) return true;
    return false;
}
