#ifndef CELLPATTERN_H
#define CELLPATTERN_H

#include <vector>
#include "cell.h"

/**
 * @brief Typ-Vereinfachung
 */
typedef std::vector<std::vector<Cell> > CellArray;

/**
 * @brief Klasse zum Speichern und Lesen von benutzerdefinierten<BR>
 * EasyLogic-Elementen
 */
class CellPattern : public CellArray
{
public:

    /**
     * @brief Konstruktor zum Erzeugen einer CellPattern-Instanz mit<BR>
     * vordefinierten Attributen
     * @param p_caArray Vorgefertige Map, die angenommen werden soll
     * @param p_qsName Name des benutzerdefinierten Elements
     * @see CellArray
     */
    CellPattern(CellArray &p_caArray, const QString &p_qsName);

    /**
     * @brief Konsturktor zum Erzeugen einer CellPattern-Instanz mit<BR>
     * vordefinierten Attributen
     * @param p_caArray Vorgefertige Map, die angenommen werden soll
     * @param p_sName Name des benutzerdefinierten Elements
     */
    CellPattern(CellArray &p_caArray, const char *p_sName);

    /**
     * @brief Standard-Konstruktor zum Erzeugen einer CellPattern-Instanz
     */
    CellPattern();

    /**
     * @brief Konsturktor zum Erzeugen einer CellPattern-Instanz<BR>
     * mit vordefiniertem, benutzerdefiniertem Namen
     * @param p_qsName Name des benutzerdefinierten Elements
     */
    CellPattern(const QString &p_qsName);

    /**
     * @brief Konsturktor zum Erzeugen einer CellPattern-Instanz<BR>
     * mit vordefiniertem, benutzerdefiniertem Namen
     * @param p_sName Name des benutzerdefinierten Elements
     */
    CellPattern(const char *p_sName);

    /**
     * @brief Gibt den Namen des aktuellen Elements zurück
     * @return Element-Name
     */
    const QString getNameQString() const;

    /**
     * @brief Gibt den Namen des aktuellen Elements zurück
     * @return Element-Name
     */
    const char *getName() const;

    /**
     * @brief Legt den Namen des aktuellen Elements fest
     * @param p_qsName Anzunehmender Element-Name
     */
    void setName(const QString p_qsName);

    /**
     * @brief Legt den Namen des aktuellen Elements fest
     * @param p_sName Anzunehmender Element-Name
     */
    void setName(const char *p_sName);

private:

    /**
     * @brief Name des aktuellen Elements
     */
    QString m_qsName;
};

#endif // CELLPATTERN_H
