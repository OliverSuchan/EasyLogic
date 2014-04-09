#include "cellpattern.h"

CellPattern::CellPattern(CellArray &p_caArray, const std::string &p_sName) : CellArray(p_caArray), m_sName(p_sName)
{

}

const std::string &CellPattern::getName() const
{
    return m_sName;
}

void CellPattern::setName(char *p_sName)
{
    m_sName = p_sName;
}
