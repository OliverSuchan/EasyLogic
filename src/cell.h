#ifndef CELL_H
#define CELL_H

#include <exception>
#include <iostream>
#include "globals.h"

/**
 * @brief Klasse um eine vollständige WireWorld-Zelle beschreiben zu können
 */
class Cell
{
public:

    /**
     * @brief Standard-Konstruktor zum Erzeugen einer Cell-Instanz
     */
    Cell();

    /**
     * @brief Konstruktor zum Erzeugen einer Zelle mit vordefiniertem Status
     * @param p_sState Status den die Zelle annehmen soll
     */
    Cell(Globals::State p_sState);

    /**
     * @brief Weist der Zelle den nächsten Status zu - "Modulo3-Zähler"
     */
    void nextState();

    /**
     * @brief Gibt den Status der Zelle zurück
     * @see Globals::State
     * @return Status der Zelle
     */
    const Globals::State getState() const;

    /**
     * @brief Legt den Status der Zelle fest
     * @param p_sValue Der anzunehmende Status
     */
    void setState(Globals::State p_sValue);

private:

    /**
     * @brief Aktueller Status der Zeller
     */
    Globals::State m_sCellState;
};

#endif // ZELLE_H
