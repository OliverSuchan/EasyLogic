#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include "globals.h"
#include "cell.h"

typedef std::vector<std::vector<Cell> > CellArray;

class Automaton
{
public:
    Automaton(long p_lHeight, long p_lWidth);
    void setCell(Cell p_cValue, long p_lAbcissa, long p_lOrdinant);
    long nextGeneration();

private:
    bool checkCell(long p_lAbscissa, long p_lOrdinant);
    CellArray m_caCells;
    CellArray m_caAuxilliaryArray;
    long m_lCurrentGen;
};

#endif // AUTOMATON_H
