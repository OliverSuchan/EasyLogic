#include "automaton.h"

Automaton::Automaton()
{
    m_caCells.push_back(std::vector<Cell>());
}

Automaton::Automaton(int p_lHeight, int p_lWidth)
{
    for(int lAbscissas = 0; lAbscissas < p_lWidth; lAbscissas++)
    {
        m_caCells.push_back(std::vector<Cell>());
        for(long lOrdinants = 0; lOrdinants < p_lHeight;lOrdinants++) m_caCells.at(lAbscissas).push_back(Cell());
    }
}

void Automaton::setCell(Cell p_cValue, int p_lAbcissa, int p_lOrdinant)
{
    m_caCells.at(p_lAbcissa).at(p_lOrdinant) = p_cValue;
}

long Automaton::nextGeneration()
{
    m_caAuxilliaryArray = m_caCells;
    for(int lCounterAbscissas = 0; lCounterAbscissas < m_caCells.size(); lCounterAbscissas++)
    {
        for(int lCounterOrdinants = 0; lCounterOrdinants < m_caCells.at(lCounterAbscissas).size(); lCounterOrdinants)
        {
            Cell cCurrentCell = m_caCells.at(lCounterAbscissas).at(lCounterOrdinants);
            if(cCurrentCell.getState() == Globals::CONDUCTOR)
            {
                if(checkCell(lCounterAbscissas, lCounterOrdinants))
                    cCurrentCell.nextState();
            }
            else
            {
                cCurrentCell.nextState();
            }
        }
    }
    m_caCells = m_caAuxilliaryArray;
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

bool Automaton::checkCell(int p_lAbscissa, int p_lOrdinant)
{
    short sElectronCounter = 0;
    for(int lCounterAbscissas = p_lAbscissa - 1; lCounterAbscissas < p_lAbscissa + 1; lCounterAbscissas++)
    {
        for(int lCounterOrdinants = p_lOrdinant - 1; lCounterOrdinants < p_lOrdinant + 1; lCounterOrdinants++)
        {
            if(lCounterAbscissas != p_lAbscissa && lCounterOrdinants != p_lOrdinant)
            {
                try
                {
                    if(m_caAuxilliaryArray.at(lCounterOrdinants).at(lCounterOrdinants).getState() == Globals::HEAD)
                    {
                        sElectronCounter++;
                    }
                }
                catch(std::exception)
                {}
            }
        }
    }
    if(sElectronCounter >= 1 && sElectronCounter <= 2)
        return true;
    return false;
}
