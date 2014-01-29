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
    const Globals::State getState()const;
private:
    Globals::State m_sCellState;
};

#endif // ZELLE_H
