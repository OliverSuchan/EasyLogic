#ifndef DATAIO_H
#define DATAIO_H

#include <QString>
#include <QDir>
#include "cellpattern.h"
#include "globals.h"

class DataIO
{
private:
    DataIO();
    DataIO(DataIO &p_dioRef);
    DataIO &operator=(DataIO &p_dioRef);
    QString m_qsPath;
    const QString m_qsFilenameExtension = ".pattern";
public:
    static DataIO &getInstance();
    DataIO &operator<<(const CellPattern &p_cpPattern);
    CellPattern getPattern(const char *p_sName);
    CellPattern getPattern(QString p_qsName);
    std::vector<const char *> getExistingCellPatterns();
    std::vector<QString> getExistingCellPatternsQString();
    void removePattern(const char *p_sName);
    void removePattern(QString p_qsName);
    const char *getPath() const;
    QString getPathQString() const;
    void setPath(const char *p_sPath);
    void setPath(QString p_qsPath);
    QString getFileExtension();

};

class DirectoryNotFoundException : public std::exception{};

class FileNotFoundException : public std::exception{};

class FileAlreadyExistsException : public std::exception{};



#endif // DATAIO_H
