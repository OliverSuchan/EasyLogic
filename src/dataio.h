#ifndef DATAIO_H
#define DATAIO_H

#include <fstream>
#include <QRegExp>
#include "cellpattern.h"
#include "globals.h"

#define PATH "C:/Users/Philipp/Documents/GitHub/build-EasyLogic-Desktop_Qt_5_1_1_MinGW_32bit-Debug/debug/test.txt"
#define INDEX_SIZE 8

class DataIO
{
private:
    DataIO();
    DataIO(DataIO &p_dioRef);
    DataIO &operator=(DataIO &p_dioRef);
public:
    static DataIO &getInstance();
    DataIO &operator<<(const CellPattern &p_cpPattern);
    CellPattern getPattern(const char *p_sName);
    std::vector<CellPattern> getAllCellPatterns();

};

#endif // DATAIO_H
