#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QMenuBar>
#include <QMenu>
#include <QtMath>
#include <QAction>
#include <QIcon>
#include <QPixmap>
#include <QRect>
#include <iostream>
#include <limits>
#include "globals.h"
#include "dataio.h"
#include "savepatternwindow.h"
#include "wireworldwidget.h"

/**
 * @brief GUI-Klasse, welche den gesamten logischen<BR>
 * Programmablauf visualierst und bedienbar macht.<BR>
 * Wie zum Beispiel:<BR>
 * - Elemente speichern/ laden<BR>
 * - Map bearbeiten<BR>
 * - Simulation starten/ stoppen<BR>
 * - Nächster/ vorheriger Simulationsschritt<BR>
 * - Zoom<BR>
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Standard-Konstruktor zum Erzeugen einer MainWindow-Instanz
     * @param p_qwParent "Elternteil" der MainWindow-Instanz
     */
    MainWindow(QWidget *p_qwParent = 0);

    /**
     * @brief Konstruktor zum Erzeugen einer MainWindow-Instanz,<BR>
     * mit vordefinierten Attributen
     * @param p_iHeight Höhe der Map
     * @param p_iWidth Breite der Map
     * @param p_qwParent "Elternteil" der MainWindow-Instanz
     */
    MainWindow(int p_iHeight, int p_iWidth, QWidget *p_qwParent = 0);
    ~MainWindow();

protected:

    /**
     * @brief Wird aufgerufen, sobald das Fenster eine neue Größe bekommt
     * @param p_pqrEvent Größen-Änderungs-Event
     */
    void resizeEvent(QResizeEvent *p_pqrEvent);

    /**
     * @brief Wird ausgeführt, sobald das Fenster neu gezeichnet werden soll<BR>
     * ( Aufruf erfolgt durch repaint-Methode)
     * @param p_pqpePaintEvent Zeichnen-Event
     */
    void paintEvent(QPaintEvent *p_pqpePaintEvent);

private:

    /**
     * @brief Control zum Zeichnen der Map
     * @see WireWorldWidget
     */
    WireWorldWidget *m_pwwwWire;

    /**
     * @brief Button um die Simulation zu starten
     */
    QPushButton *m_pqpbStartButton;

    /**
     * @brief Button um die Simulation zu stoppen
     */
    QPushButton *m_pqpbStopButton;

    /**
     * @brief Button um den aktuellen Status der Map zu speichern<BR>
     * umso Generationen zurück rechnen zu können
     */
    QPushButton *m_pqpbSaveButton;

    /**
     * @brief Button um X Simulations-Schritte nach vorne zu gehen
     */
    QPushButton *m_pqpbNextStepButton;

    /**
     * @brief Button um X Simulations-Schritte nach hinten zu gehen
     */
    QPushButton *m_pqpbPreviousStepButton;

    /**
     * @brief Anzahl der Schritte die nach vorne/ hinten gemacht werden sollen
     */
    QSpinBox *m_pqsbStepBox;

    /**
     * @brief Schieberegler um den Zoom-Faktor zu in- oder dekrementieren
     */
    QSlider *m_pqsZoomSlider;

    /**
     * @brief Menu-Bar um den aktuellen Status zu ändern oder<BR>
     * Elemente zu laden bzw. zu speichern
     */
    QMenuBar *m_pqmbMenuBar;

    /**
     * @brief Menu zum Auswählen des aktuellen Statuses
     */
    QMenu *m_pqmItemsMenu;

    /**
     * @brief Menu zum Speichern bzw. Laden von Elementen
     */
    QMenu *m_pqmPatternsMenu;

    /**
     * @brief Ändert den Status zu "Leer"
     */
    QAction *m_pqaEmptyState;

    /**
     * @brief Ändert den Status zu "Leiter"
     */
    QAction *m_pqaConductorState;

    /**
     * @brief Ändert den Status zu "Elektronen-Kopf"
     */
    QAction *m_pqaHeadState;

    /**
     * @brief Ändert den Status zu "Elektronen-Ende"
     */
    QAction *m_pqaTailState;

    /**
     * @brief Richtet die GUI ein
     */
    void setupUI();

    /**
     * @brief Richtet das WireWorldWidget ein
     * @see WireWorldWidget
     */
    void init();

private slots:

    /**
     * @brief Wird ausgeführt, wenn der Status geändert werden soll
     */
    void itemTriggeredAction();

    /**
     * @brief Wird ausgeführt, sobald ein Element geladen werden soll.<BR>
     * Erneuert die Liste der Elemente im aktuellen Verzeichnis
     * @see DataIO::getExistingCellPatterns
     */
    void reloadPatternList();
};

#endif // MAINWINDOW_H
