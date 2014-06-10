#ifndef CELL_H
#define CELL_H

#include <exception>
#include <iostream>
#include "globals.h"

class Cell
{
public:
    Cell();
    Cell(Globals::State p_sState);
    void nextState();
    void setElectron();
    const Globals::State getState() const;
    void setState(Globals::State p_sValue);

private:
    Globals::State m_sCellState;
};

#endif // ZELLE_H
