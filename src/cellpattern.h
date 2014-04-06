#ifndef CELLPATTERN_H
#define CELLPATTERN_H

#include <vector>
#include "cell.h"

typedef std::vector<std::vector<Cell> > CellArray;

class CellPattern : public CellArray
{
public:
    CellPattern(CellArray &p_caArray, const std::string &p_sName);
    const std::string &getName() const;
    void setName(char *p_sName);
private:
    std::string m_sName;
};

#endif // CELLPATTERN_H
