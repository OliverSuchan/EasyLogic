#ifndef MAPSETTINGSWINDOW_H
#define MAPSETTINGSWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <limits>
#include <iostream>
#include "globals.h"
#include "mainwindow.h"

/**
 * @brief Start-Fenster, um benutzerdefinierte Einstellungen festzulegen,<BR>
 * wie zum Beispiel:<BR>
 * - Map-Größe<BR>
 * - Farben der Zell-Status
 */
class MapSettingsWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Standard-Konstruktor zum Erzeugen einer MapSettingsWindow-Instanz
     * @param parent "Elternteil" der MapSettingsWindow-Instanz
     */
    explicit MapSettingsWindow(QWidget *parent = 0);

protected:

    /**
     * @brief Wird aufgerufen, sobald die GUI neu gezeichnet werden soll<BR>
     * ( Aufgerufen durch repaint-Methode)
     */
    void paintEvent(QPaintEvent *);

private slots:

    /**
     * @brief Wird aufgerufen, wenn der "Anwenden"-Button gedrückt wurde
     */
    void applyButtonClickEvent();

    /**
     * @brief Wird aufgerufen, wenn die Farbe eines Zell-Statuses geändert werden soll
     * @param p_iIndex Index der zu ändernden Zell-Status-Farbe
     * @param p_pqpbPushButton Button der Zell-Status-Farbe
     */
    void changeColor(int p_iIndex, QPushButton *p_pqpbPushButton);

private:

    /**
     * @brief Numerisches Feld zum Festlegen der Map-Breite
     */
    QSpinBox *m_pqsbWidthSpinBox;

    /**
     * @brief Numerisches Feld zum Festlegen der Map-Höhe
     */
    QSpinBox *m_pqsbHeightSpinBox;

    /**
     * @brief "Anwenden"-Button, um Einstellungen anzuwenden
     */
    QPushButton *m_pqpbApplyButton;

    /**
     * @brief Farb-Wähl-Dialog, um die Status der Zellen zu ändern
     */
    QColorDialog *m_pqcdColorPicker;

    /**
     * @brief Label, dass ein "Mal" zwischen der Breite und Höhe<BR>
     * symbolisieren soll
     */
    QLabel *m_pqlblProductLabel;

};

#endif // MAPSETTINGSWINDOW_H
