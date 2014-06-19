#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QPoint>
#include <iostream>
#include <vector>
#include "globals.h"
#include "cell.h"

/**
 * @brief Typ-Vereinfachung
 */
typedef std::vector<std::vector<Cell> > CellArray;

/**
 * @brief
 * Herz des EasyLogic-Projekts<BR>
 * Übernimmt jegliche Logik - Verbeitungsregeln werden angewendet
 */
class Automaton
{
public:
    /**
     * @brief Standard-Konstruktor um eine Automaton-Instanz zu erzeugen<BR>
     * bei der die Map-Größe 1x1 beträgt
     */
    Automaton();

    /**
     * @brief Konstruktor zum Erzeugen einer Automaton-Instanz<BR>
     * mit benutzerdefinierter Map-Größe
     * @param p_iHeight Höhe der zu erzeugenden Map
     * @param p_iWidth Breite der zu erzeugenden Map
     */
    Automaton(int p_iHeight, int p_iWidth);

    /**
     * @brief Legt eine Zelle an einer bestimmten Position in der Map fest
     * @param p_cValue Die zu speichernde Zelle
     * @param p_qpCoordinates Position an die die Zelle in der Map gespeichert werden soll
     * @see Cell
     * @see m_caCells
     */
    void setCell(Cell p_cValue, QPoint p_qpCoordinates);

    /**
     * @brief Legt eine Zelle an einer bestimmten Position in der Map fest
     * @param p_cValue Die zu speichernde Zelle
     * @param p_iAbscissa X-Koordinante an der die Zelle in der Map gespeichert werden soll
     * @param p_iOrdinant Y-Koordinante an der die Zelle in der Map gespeichert werden soll
     * @see Cell
     * @see m_caCells
     */
    void setCell(Cell p_cValue, int p_iAbscissa, int p_iOrdinant);

    /**
     * @brief Legt den Status einer Zelle an einer bestimmten Positon fest<BR>
     * @see Globals::State
     * @param p_sValue Neuer Status für die vorhandene Zelle
     * @param p_iAbscissa X-Koordinante der Zelle, wo der Status gespeichert werden soll
     * @param p_iOrdinant Y-Koordinante der Zelle, wo der Status gespeichert werden soll
     * @see m_caCells
     */
    void setCellState(Globals::State p_sValue, int p_iAbscissa, int p_iOrdinant);

    /**
     * @brief Legt den Status einer Zelle an einer bestimmten Positon fest<BR>
     * @see Globals::State
     * @param p_sValue Neuer Status für die vorhandene Zelle
     * @param p_qpCellPosition Position der Zelle, wo der Status gespeichert werden soll
     * @see m_caCells
     */
    void setCellState(Globals::State p_sValue, QPoint p_qpCellPosition);

    /**
     * @brief Generiert eine beliebige Anzahl an Generationen vorwärts
     * @param p_lGenerationCount Anzahl der Generationen die generiert werden sollen<BR>
     * standardmäßig: 1 Generation
     * @return Generation, wo man sich nach der Generierung befindet
     * @see m_lCurrentGen
     */
    long nextGeneration(long p_lGenerationCount = 1);

    /**
     * @brief Generiert eine beliebige Anzahl an Generationen rückwärts
     * @param p_lGenerationCount Anzahl der Generationen die generiert werden sollen<BR>
     * standardmäßig: 1 Generation
     * @return Generation, wo man sich nach der Generierung befindet
     * @see m_lCurrentGen
     */
    long previousGeneration(long p_lGenerationCount = 1);

    /**
     * @brief Liefert den Status einer Zelle an einer bestimmten Position in der Map
     * @param p_iX X-Koordinante der Zelle, dessen Status abgefragt werden soll
     * @param p_iY Y-Koordinante der Zelle, dessen Status abgefragt werden soll
     * @return Satus
     * @see Globals::State
     * @see m_caCells
     */
    const Globals::State getStateAt(int p_iX, int p_iY)const;

    /**
     * @brief Gibt die Breite der Map zurück
     * @return Map-Breite
     * @see m_caCells
     */
    int getWidth()const;

    /**
     * @brief Gibt die Höhe der Map zurück
     * @return Map-Höhe
     * @see m_caCells
     */
    int getHeight()const;

    /**
     * @brief Liefert die aktuelle Generation
     * @return Aktuelle Generation
     * @see m_lCurrentGen
     */
    long getCurrentGen() const;

    /**
     * @brief Speichert den aktuellen Status der Map ab,<BR>
     * um zu einem späteren Punkt Generationen zu diesem Punkt zurückrechnen<BR>
     * zu können
     */
    void setGenerationArray();

    /**
     * @brief Überprüft ob es möglich ist vorherige<BR>
     * Generationen zurück zu rechnen
     * @see setGenerationArray
     * @return Wahrheitswert der angibt ob es möglich ist, oder nicht
     */
    bool canGeneratePreviousGeneration();

private:
    /**
     * @brief Überprüft Verbreitungsregeln auf Richtigkeit
     * @param p_iAbscissa X-Koordinante der zu überprüfenden Zelle
     * @param p_iOrdinant Y-Koordinante der zu überprüfenden Zelle
     * @return Wahrheitswert der angibt, ob die Zelle den nächsten<BR>
     * Status annehmen kann
     * @see nextGeneration
     * @see previousGeneration
     */
    bool checkCell(int p_iAbscissa, int p_iOrdinant);

    /**
     * @brief Array das lediglich zum Generieren<BR>
     * der nächsten Generationen verwendet wird
     * @see nextGeneration
     * @see previousGeneration)
     */
    CellArray m_caAuxilliaryArray;

    /**
     * @brief Array das die aktuelle Map darstellt,<BR>
     * die gezeichnet werden soll
     */
    CellArray m_caCells;

    /**
     * @brief Array um Generationen zurück rechnen zu können
     */
    CellArray m_caGenerationPurposesArray;

    /**
     * @brief Aktuelle Generation
     */
    long m_lCurrentGen;
};

#endif // AUTOMATON_H
