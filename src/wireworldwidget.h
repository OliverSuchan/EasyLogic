#ifndef WIREWORLDWIDGET_H
#define WIREWORLDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QPoint>
#include <thread>
#include <future>
#include <mutex>
#include "globals.h"
#include "automaton.h"
#include "dataio.h"
#include "cellpattern.h"

/**
 * @brief Widget, welches den Simulationsprozess<BR>
 * des zellulären Automaten - WireWorld - visualisiert
 */
class WireWorldWidget : public QWidget
{
    Q_OBJECT

private:

    /**
     * @brief Zellulärer Automat, der visualisiert werden soll
     * @see Automaton
     */
    Automaton m_aAutomaton;

    /**
     * @brief Aktueller Status, um Zellen zu bearbeitenb<BR>
     * Dieser Status wird auf alle Zellen, die angeklickt werden, angewendet
     */
    Globals::State m_sCurrentState;

    /**
     * @brief Spezieller Wahrheitswert der threadübergreifend<BR>
     * erreichbar ist. Legt fest, ob Generationen<BR>
     * automatisch generiert werden sollen
     */
    std::atomic<bool> m_bAutoNextGeneration;

    /**
     * @brief Thread zur Ausführung der "paint-loop"
     */
    std::thread *m_sthrUpdateThread;

    /**
     * @brief Mutex, um Variablen die sich in einem anderen Thread befinden<BR>
     * ansprechen zu können, ohne, dass Probleme auftreten.<BR>
     * Erhöhte Thread-Sicherheit
     */
    std::mutex m_threadMutex;

    /**
     * @brief Spezieller Wahrheitswert der threadübergreifend<BR>
     * erreichbar ist. Legt fest, ob der "repaint"-Vorgang<BR>
     * abgeschlossen ist und die nächsten Aktionen ausgeführt<BR>
     * werden können
     */
    std::atomic<bool> m_bCanUpdate;

    /**
     * @brief Spezieller Ganzzahlwert der threadübergreifend<BR>
     * erreichbar ist. Bildet die Anzahl der Frames per Second
     */
    std::atomic<int> m_iFPS;

    /**
     * @brief Wird verwendet, sobald man einen Bereich der Map<BR>
     * selektieren möchte. Speichert die Maus Positionen an der<BR>
     * das Rechteck für den ausgewählten Bereich erzeugt wurde
     */
    QPoint m_qpOldMousePosition;

    /**
     * @brief Rechteck, das den ausgewählten Bereich der Map<BR>
     * darstellt.
     */
    QRect m_qrSelectedArea;

    /**
     * @brief Spezieller Wahrheitswert der threadübergreifend<BR>
     * erreichbar ist. Gibt an, ob man Bereiche auswählen kann
     */
    std::atomic<bool> m_bCanSelectArea;

protected:

    /**
     * @brief Wird aufgerufen, sobald eine Taste gedrückt wird
     * @param Tasten-Event
     */
    void keyPressEvent(QKeyEvent *p_pqkeEvent);

    /**
     * @brief Wird aufgerufen, sobald eine Maustaste gedrückt wird
     * @param Maus-Event
     */
    void mousePressEvent(QMouseEvent *p_qmeEvent);

    /**
     * @brief Wird aufgerufen sobald sich die Maus bewegt<BR>
     * und zuvor eine Maustaste gedrückt wurde
     * @param Maus-Event
     */
    void mouseMoveEvent(QMouseEvent *p_qmeEvent);

    /**
     * @brief Wird aufgerufen, wenn die GUI neu gezeichnert werden soll.<BR>
     * ( Aufruf erfolgt durch "repaint"-Methode)
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Wird aufgerufen, wenn das Mausrad betätigt wird
     * @param Mausrad-Event
     */
    void wheelEvent(QWheelEvent *p_pqweWheelEvent);

private slots:

    /**
     * @brief update
     */
    void update();

    /**
     * @brief Wird jede Sekunde aufgerufen und gibt aus, wie viele<BR>
     * Bilder pro Sekunde berechnet wurden
     */
    void framesPerSecond();

signals:

    /**
     * @brief Wird emittiert sobald das Widget geklickt wurde
     */
    void clicked();

public:

    /**
     * @brief Standard-Konstruktor zum Erzeugen<BR>
     * einer WireWorldWidget-Instanz
     * @param "Elternteil" der zu erzeugenden WireWorldWidget-Instanz
     */
    WireWorldWidget(QWidget *p_pqwParent = 0);

    /**
      * @brief Standard-Destruktor zum ordnungsgemäßen<BR>
      * Löschen der WireWorldWidget-Instanz
      */
    ~WireWorldWidget();

    /**
     * @brief Liefert den aktuellen zellulären Automat des Widgets
     * @return Aktueller zellulärer Automat
     * @see Automaton
     */
    Automaton &getAutomaton();

    /**
     * @brief Legt den zellulären Automaten der aktuellen Instanz fest
     * @param p_aAutomaton Neuer zellulärer Automat
     * @see Automaton
     */
    void setAutomaton(Automaton p_aAutomaton);

    /**
     * @brief Gibt zurück, ob aktuell Generationen<BR>
     * automatisch generiert werden
     * @return Status der automatischen Generierung
     * @see m_bAutoNextGeneration
     */
    bool getAutoNextGeneration() const;

    /**
     * @brief Legt fest, ob Generationen automatisch<BR>
     * werden sollen
     * @param p_bAutoNextGeneration Wahrheitswert für automatische Generierung
     * @see m_bAutoNextGeneration
     */
    void setAutoNextGeneration(bool p_bAutoNextGeneration);

    /**
     * @brief Ändert die Größe der WireWorldWidget-Instanz (überschrieben)
     * @param p_iWidth Neue Breite der Instanz
     * @param p_iHeight Neue Größe der Instanz
     */
    void resize(int p_iWidth, int p_iHeight);

    /**
     * @brief Legt den aktuellen Status zum Bearbeiten der Map fest
     * @param p_sNewState Aktueller Status
     * @see Globals::State
     * @see m_sCurrentState
     */
    void setCurrentState(Globals::State p_sNewState);

    /**
     * @brief Konvertiert die aktuelle Maus-Position in Koordinaten<BR>
     * zum Beschreiben einer Zelle
     * @return Zell-Position
     */
    QPoint convertMousePosToCellPos();

    /**
     * @brief Fügt ein benutzerdefiniertes Element an einer bestimmten<BR>
     * Stelle ein. (Hauptsächlich Maus-Position)
     * @param p_cpCellPattern Einzufügendes Element
     * @param p_qpCellPatternPositon Position des einzufügenden Elements
     * @see CellPattern
     */
    void insertCellPattern(CellPattern p_cpCellPattern, QPoint p_qpCellPatternPositon);

    /**
     * @brief Aktiviert die Möglichkeit Bereiche auszuwählen
     */
    void activateAreaSelection();

    /**
     * @brief Deaktiviert die Möglichkeit Bereiche auszuwählen
     */
    void deactivateAreaSelection();

    /**
     * @brief Gibt den aktuell ausgewählten Bereich zurück
     * @return Aktuell ausgewählte Zellen
     */
    CellArray getSelectedArea();

    /**
     * @brief Wählt die gesamte Map aus
     */
    void selectAll();

    /**
     * @brief Entwählt die gesamte Map
     */
    void unselectAll();

};

#endif // WIREWORLDWIDGET_H
