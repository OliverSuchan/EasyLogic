#ifndef CELLPATTERN_H
#define CELLPATTERN_H

#include <vector>
#include "cell.h"

typedef std::vector<std::vector<Cell> > CellArray;

class CellPattern : public CellArray
{
public:
    CellPattern(CellArray &p_caArray, const QString &p_qsName);
    CellPattern(CellArray &p_caArray, const char *p_sName);
    CellPattern();
    CellPattern(const QString &p_qsName);
    CellPattern(const char *p_sName);
    const QString getNameQString() const;
    const char *getName() const;
    void setName(const QString p_qsName);
    void setName(const char *p_sName);
private:
    QString m_qsName;
};

#endif // CELLPATTERN_H
