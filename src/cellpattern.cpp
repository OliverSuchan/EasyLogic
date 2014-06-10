#include "cellpattern.h"

CellPattern::CellPattern(CellArray &p_caArray, const QString &p_qsName) : CellArray(p_caArray), m_qsName(p_qsName)
{
}

CellPattern::CellPattern(CellArray &p_caArray, const char *p_sName) : CellArray(p_caArray), m_qsName(p_sName)
{
}

CellPattern::CellPattern() : CellArray(), m_qsName("")
{
}

CellPattern::CellPattern(const QString &p_qsName) : CellArray(), m_qsName(p_qsName)
{
}

CellPattern::CellPattern(const char *p_sName) : CellArray(), m_qsName(p_sName)
{
}

const QString CellPattern::getNameQString() const
{
    return m_qsName;
}

const char *CellPattern::getName() const
{
    return m_qsName.toStdString().c_str();
}

void CellPattern::setName(const QString p_qsName)
{
    m_qsName = p_qsName;
}

void CellPattern::setName(const char *p_sName)
{
    m_qsName = p_sName;
}
