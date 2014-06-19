#ifndef GLOBALS_H
#define GLOBALS_H

#include <QColor>

/**
 * @brief Singleton-Klasse, die von fast allen Klassen<BR>
 * benötigt wird
 */
class Globals
{
public:

    /**
     * @brief Enum zum Beschreiben der verschiedenen<BR>
     * Status einer Zelle
     */
    enum State {
        EMPTY, CONDUCTOR, HEAD, TAIL
    };

    /**
     * @brief Liefert die aktuelle Globals-Singleton-Instanz
     * @return Globals-Singleton-Instanz
     */
    static Globals &getInstance();

    /**
     * @brief Breite der zu zeichnenden Zellen<BR>
     * Stanardmäßig: 32 Pixel
     */
    int m_dCellWidth;

    /**
     * @brief Höhe der zu zeichnenden Zellen<BR>
     * Stanardmäßig: 32 Pixel
     */
    int m_dCellHeight;

    /**
     * @brief Anfangs X-Position der Map.<BR>
     * Wird für das Map-Scrolling benötigt<BR>
     * Standardmäßig: 0 Pixel
     */
    int m_iX;

    /**
     * @brief Anfangs Y-Position der Map.<BR>
     * Wird für das Map-Scrolling benötigt<BR>
     * Standardmäßig: 0 Pixel
     */
    int m_iY;

    /**
     * @brief Zoom-Faktor der Map<BR>
     * Standardmäßig: 100 Prozent
     */
    double m_dZoomFactor;

    /**
     * @brief Die 4 verschiedenen Namen der Zell-Status:<BR>
     * Standardmäßig:<BR>
     * - Leer<BR>
     * - Leiter<BR>
     * - Elektronen-Kopf<BR>
     * - Elektronen-Ende<BR>
     */
    QString m_rqstStateNames[4];

    /**
     * @brief Die 4 verschiedenen Farben der Zell-Status:<BR>
     * Standardmäßig:<BR>
     * - Schwarz<BR>
     * - Gelb<BR>
     * - Blau<BR>
     * - Rot
     */
    QColor m_rqcColors[4];


private:

    /**
     * @brief Standard-Konstruktor zum Erzeugen einer Globals-Instanz<BR>
     * Private, da es eine Singleton-Designstruktur ist
     */
    Globals();

    /**
     * @brief Standard-Kopierkonstruktur<BR>
     * Keine Aufgabe, da es eine Singleton-Designstruktur ist
     * @param p_gloRef Zu kopieren Globals-Instanz
     */
    Globals(Globals &p_gloRef);

    /**
     * @brief Überladener Zuweisungsoperator<BR>
     * Keine Aufgabe, da es eine Singleton-Designstruktur ist
     * @param p_gloRef Zu verwendende Globals-Instanz
     * @return Globals-Referenz
     */
    Globals &operator=(Globals &p_gloRef);
};

#endif // GLOBALS_H
