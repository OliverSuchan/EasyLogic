#include "dataio.h"

DataIO::DataIO()
{
}

DataIO::DataIO(DataIO &p_dioRef)
{
}

DataIO &DataIO::operator=(DataIO &p_dioRef)
{
    return *this;
}

DataIO &DataIO::getInstance()
{
    static DataIO dioInstance;
    return dioInstance;
}

DataIO &DataIO::operator<<(const CellPattern &p_cpPattern)
{
        QDir qdDir(m_qsPath);
        if(!qdDir.exists()){
            qdDir.cdUp();
            qdDir.mkdir(m_qsPath);
        }
        QFile qfOut(QString(m_qsPath)
                    + p_cpPattern.getName()
                    + m_qsFilenameExtendion);
        if(qfOut.exists()) throw FileAlreadyExistsException();
        qfOut.open(QIODevice::WriteOnly);
        qfOut.write(p_cpPattern.getName(), p_cpPattern.getNameQString().length());
        qfOut.putChar('\n');
        for(auto aRows : p_cpPattern)
        {
            for(Cell cCell : aRows)
            {
                qfOut.putChar(cCell.getState());
            }
            qfOut.putChar('\n');
        }
    qfOut.close();
    return *this;
}

CellPattern DataIO::getPattern(const char *p_sName)
{
        QDir qdDir(m_qsPath);
        if(!qdDir.exists()) throw DirectoryNotFoundException();
        QFile qfIn(m_qsPath + QString(p_sName) + m_qsFilenameExtendion);
        if(!qfIn.open(QIODevice::ReadOnly)) throw FileNotFoundException();
        CellPattern cpResultPattern(qfIn.readLine().constData());
        while(qfIn.canReadLine()){
            std::vector<Cell> cvResultRow;
            for(auto aByte : qfIn.readLine()){
                if(aByte <= Globals::TAIL){
                    cvResultRow.push_back(Cell(static_cast<Globals::State>(aByte)));
                }
            }
            cpResultPattern.push_back(cvResultRow);
        }
        qfIn.close();
        return cpResultPattern;
}

CellPattern DataIO::getPattern(QString p_qsName)
{
    QDir qdDir(m_qsPath);
    if(!qdDir.exists()) throw DirectoryNotFoundException();
    QFile qfIn(m_qsPath + p_qsName + m_qsFilenameExtendion);
    if(!qfIn.open(QIODevice::ReadOnly)) throw FileNotFoundException();
    CellPattern cpResultPattern(qfIn.readLine().constData());
    while(qfIn.canReadLine()){
        std::vector<Cell> cvResultRow;
        for(auto aByte : qfIn.readLine()){
            if(aByte <= Globals::TAIL){
                cvResultRow.push_back(Cell(static_cast<Globals::State>(aByte)));
            }
        }
        cpResultPattern.push_back(cvResultRow);
    }
    qfIn.close();
    return cpResultPattern;
}

std::vector<const char *> DataIO::getExistingCellPatterns()
{
    QDir qdDir(m_qsPath);
    if(!qdDir.exists()) throw DirectoryNotFoundException();
    std::vector<const char *> vcResultNames;
    for(QString name : qdDir.entryList(QStringList(QString("*")+m_qsFilenameExtendion)))
        vcResultNames.push_back(name.toStdString().c_str());
    return vcResultNames;
}

std::vector<QString> DataIO::getExistingCellPatternsQString()
{
    QDir qdDir(m_qsPath);
    if(!qdDir.exists()) throw DirectoryNotFoundException();
    std::vector<QString> vcResultNames;
    for(QString qsName : qdDir.entryList(QStringList(QString("*")+m_qsFilenameExtendion)))
        vcResultNames.push_back(qsName);
    return vcResultNames;
}

void DataIO::removePattern(const char *p_sName)
{
    QDir qdDir(m_qsPath);
    if(!qdDir.exists())throw DirectoryNotFoundException();
    QFile qfFile(m_qsPath + QString(p_sName) + m_qsPath);
    if(!qfFile.exists())return;
    qfFile.remove();
    return;
}

void DataIO::removePattern(QString p_qsName)
{
    QDir qdDir(m_qsPath);
    if(!qdDir.exists())throw DirectoryNotFoundException();
    QFile qfFile(m_qsPath + p_qsName + m_qsPath);
    if(!qfFile.exists())return;
    qfFile.remove();
    return;
}

const char *DataIO::getPath() const
{
    return m_qsPath.toStdString().c_str();
}

QString DataIO::getPathQString() const
{
    return m_qsPath;
}

void DataIO::setPath(const char *p_sPath)
{
    m_qsPath = p_sPath;
}

void DataIO::setPath(QString p_qsPath)
{
    m_qsPath = p_qsPath;
}
