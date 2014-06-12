#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QPoint>
#include <iostream>
#include <vector>
#include "globals.h"
#include "cell.h"

typedef std::vector<std::vector<Cell> > CellArray;

class Automaton
{
public:
    Automaton();
    Automaton(int p_iHeight, int p_iWidth);
    void setCell(Cell p_cValue, QPoint p_qpCoordinates);
    void setCell(Cell p_cValue, int p_iAbscissa, int p_iOrdinant);
    void setCellState(Globals::State p_sValue, int p_iAbscissa, int p_iOrdinant);
    void setCellState(Globals::State p_sValue, QPoint p_qpCellPosition);
    long nextGeneration(long p_lGenerationCount = 1);
    long previousGeneration(long p_lGenerationCount = 1);
    const Globals::State getStateAt(int p_iX, int p_iY)const;
    int getWidth()const;
    int getHeight()const;
    long getCurrentGen() const;
    void setGenerationArray();
    bool canGeneratePreviousGeneration();

private:
    bool checkCell(int p_iAbscissa, int p_iOrdinant);
    CellArray m_caAuxilliaryArray;
    CellArray m_caCells;
    CellArray m_caGenerationPurposesArray;
    long m_lCurrentGen;
};

#endif // AUTOMATON_H
