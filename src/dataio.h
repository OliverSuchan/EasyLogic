#ifndef DATAIO_H
#define DATAIO_H

#include <QString>
#include <QDir>
#include "cellpattern.h"
#include "globals.h"

/**
 * @brief Singleton-Klasse zum Lesen und Schreiben<BR>
 * von benutzerdefinierten Elementen
 * @see CellPattern
 */
class DataIO
{
private:

    /**
     * @brief Standard-Konsturktor zum Erzeugen einer DataIO-Instanz.<BR>
     * Private, da es eine Singleton-Designstruktor ist
     */
    DataIO();

    /**
     * @brief Standard-Kopierkonstruktor.<BR>
     * Keine Aufgabe, da es eine Singleton-Designstruktur ist
     * @param p_dioRef Die zu kopierende DataIO-Instanz
     */
    DataIO(DataIO &p_dioRef);

    /**
     * @brief Überladener Zuweisungsoperator.<BR>
     * Keine Aufgabe, da es eine Singleton-Designstruktur ist
     * @param p_dioRef DataIO-Instanz die verwendet werden soll
     * @return Neue DataIO-Instanz
     */
    DataIO &operator=(DataIO &p_dioRef);

    /**
     * @brief Verzeichnis, in dem nach gespeicherten Elementen gesucht werden soll
     */
    QString m_qsPath;

    /**
     * @brief Dateiendung für gespeicherte Elemente.<BR>
     * Standardmäßig: ".pattern"
     */
    QString m_qsFilenameExtension;

public:

    /**
     * @brief Liefert die DataIO-Singleton-Instanz,<BR>
     * um mit ihr Aufgaben ausführen zu können
     * @return DataIO-Singleton-Instanz
     */
    static DataIO &getInstance();

    /**
     * @brief Überladener Left-Shift-Operator,<BR>
     * um benutzerdefinierte Elemente zu speichern
     * @param p_cpPattern Name des Elements<BR>
     * (ohne Dateiendung)
     * @return DataIO-Referenz
     * @throws FileAlreadyExistsException
     */
    DataIO &operator<<(const CellPattern &p_cpPattern);

    /**
     * @brief Läd ein zuvor gespeichertes Element,<BR>
     * sofern dieses existiert
     * @param p_sName Name des Elements, das geladen werden soll
     * @return CellPattern-Instanz die dem gespeicherten Element entspricht
     * @see CellPattern
     * @throws FileNotFoundException
     */
    CellPattern getPattern(const char *p_sName);

    /**
     * @brief Läd ein zuvor gespeichertes Element,<BR>
     * sofern dieses existiert
     * @param p_qsName Name des Elements, das geladen werden soll
     * @return CellPattern-Instanz die dem gespeicherten Element entspricht
     * @see CellPattern
     * @throws FileNotFoundException
     */
    CellPattern getPattern(QString p_qsName);

    /**
     * @brief Gibt alle gespeicherten Elemente im aktuellen<BR>
     * Verzeichnis als Liste zurück
     * @return Liste, bestehend aus den Elementen-Namen
     * @see m_qsPath
     * @see m_qsFilenameExtension
     * @throws DirectoryNotFoundException
     */
    std::vector<const char *> getExistingCellPatterns();

    /**
     * @brief Gibt alle gespeicherten Elemente im aktuellen<BR>
     * Verzeichnis als Liste zurück
     * @return Liste, bestehend aus den Elementen-Namen
     * @see m_qsPath
     * @see m_qsFilenameExtension
     * @throws DirectoryNotFoundException
     */
    std::vector<QString> getExistingCellPatternsQString();

    /**
     * @brief Löscht ein Element, unter Angabe seines Namens
     * @param p_sName Name des zu löschenden Elements
     * @throws DirectoryNotFoundException
     */
    void removePattern(const char *p_sName);

    /**
     * @brief Löscht ein Element, unter Angabe seines Namens
     * @param p_qsName Name des zu löschenden Elements
     * @throws DirectoryNotFoundException
     */
    void removePattern(QString p_qsName);

    /**
     * @brief Liefert den aktuellen Pfad
     * @return Aktueller Pfad
     * @see m_qsPath
     */
    const char *getPath() const;

    /**
     * @brief Liefert den aktuellen Pfad
     * @return Aktueller Pfad
     * @see m_qsPath
     */
    QString getPathQString() const;

    /**
     * @brief Legt das aktuelle Verzeichnis fest<BR>
     * und erstellt jenes, sofern es nicht vorhanden ist
     * @param p_sPath Neuer Pfad
     * @see m_qsPath
     */
    void setPath(const char *p_sPath);

    /**
     * @brief Legt das aktuelle Verzeichnis fest<BR>
     * und erstellt jenes, sofern es nicht vorhanden ist
     * @param p_qsPath Neuer Pfad
     * @see m_qsPath
     */
    void setPath(QString p_qsPath);

    /**
     * @brief Liefert die Dateiendung der Elemente
     * @return Dateiendung
     * @see m_qsFilenameExtension
     */
    QString getFileExtension();

};

/**
 * @brief Exception die geworfen wird, wenn man mit<BR>
 * einem Verzeichnis arbeitet, das gar nicht existiert
 */
class DirectoryNotFoundException : public std::exception{};

/**
 * @brief Exception die geworfen wird, wenn man mit<BR>
 * einer Datei arbeitet, die gar nicht exisitert
 */
class FileNotFoundException : public std::exception{};

/**
 * @brief Exception die geworfen wird, wenn man mit<BR>
 * einer zu speichernende Datei arbeitet, die jedoch<BR>
 * schon exisitiert
 */
class FileAlreadyExistsException : public std::exception{};



#endif // DATAIO_H
