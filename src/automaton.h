#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include "globals.h"
#include "cell.h"

typedef std::vector<std::vector<Cell> > CellArray;

class Automaton
{
public:
    Automaton();
    Automaton(int p_lHeight, int p_lWidth);
    void setCell(Cell p_cValue, int p_lAbcissa, int p_lOrdinant);
    long nextGeneration();
    const Globals::State getStateAt(int p_iX, int p_iY)const;
    int getWidth()const;
    int getHeight()const;

private:
    bool checkCell(int p_lAbscissa, int p_lOrdinant);
    CellArray m_caCells;
    CellArray m_caAuxilliaryArray;
    long m_lCurrentGen;
};

#endif // AUTOMATON_H
