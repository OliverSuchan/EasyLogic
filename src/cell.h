#ifndef CELL_H
#define CELL_H

#include <exception>
#include "globals.h"

class Cell
{
public:
    Cell();
    void nextState();
    void setElectron();
    Globals::State getState();
private:
    Globals::State m_sCellState;
};

#endif // ZELLE_H
