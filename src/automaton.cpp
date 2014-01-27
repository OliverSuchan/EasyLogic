#include "automaton.h"

Automaton::Automaton(long p_lHeight, long p_lWidth)
{
    for(long lAbscissas = 0; lAbscissas < p_lWidth; lAbscissas++)
    {
        m_caCells.push_back(std::vector<Cell>());
        for(long lOrdinants = 0; lOrdinants < p_lHeight;lOrdinants++) m_caCells.at(lAbscissas).push_back(Cell());
    }
}

void Automaton::setCell(Cell p_cValue, long p_lAbcissa, long p_lOrdinant)
{
    m_caCells.at(p_lAbcissa).at(p_lOrdinant) = p_cValue;
}

long Automaton::nextGeneration()
{
    m_caAuxilliaryArray = m_caCells;
    for(long lCounterAbscissas = 0; lCounterAbscissas < m_caCells.size(); lCounterAbscissas++)
    {
        for(long lCounterOrdinants = 0; lCounterOrdinants < m_caCells.at(lCounterAbscissas).size(); lCounterOrdinants)
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

bool Automaton::checkCell(long p_lAbscissa, long p_lOrdinant)
{
    short sElectronCounter = 0;
    for(long lCounterAbscissas = p_lAbscissa - 1; lCounterAbscissas < p_lAbscissa + 1; lCounterAbscissas++)
    {
        for(long lCounterOrdinants = p_lOrdinant - 1; lCounterOrdinants < p_lOrdinant + 1; lCounterOrdinants++)
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
