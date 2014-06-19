#ifndef SAVEPATTERNWINDOW_H
#define SAVEPATTERNWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>

/**
 * @brief Fenster, um Elemente mit Namen zu speichern
 */
class SavePatternWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Standard-Kosntruktor zum Erzeugen einer SavePatternWindow-Instanz
     * @param p_qwParent "Elternteil" der SavePatternWindow-Instanz
     */
    explicit SavePatternWindow(QWidget *p_qwParent = 0);

    /**
     * @brief Eingabefeld für den Element-Namen
     */
    QTextEdit *m_pqteNameTextEdit;

    /**
     * @brief Checkbox, um die gesamte Map auszuwählen
     */
    QCheckBox *m_pqcbSelectAllCheckBox;

    /**
     * @brief "Speichern"-Button, um den ausgewählten Bereich als<BR>
     * Element zu speichern
     */
    QPushButton *m_pqpbSaveButton;

    /**
     * @brief "Abbrechen"-Button, um den Speicher-Vorgang abzubrechen
     */
    QPushButton *m_pqpbCancelButton;

protected:

    /**
     * @brief Wird aufgerufen, sobald das Fernster geschlossen wird
     * @param p_pqceCloseEvent Schließ-Event
     */
    void closeEvent(QCloseEvent *p_pqceCloseEvent);

signals:

    /**
     * @brief Signal das emittiert wird, wenn das Fenster am Schließen ist
     */
    void closed();

};

#endif // SAVEPATTERNWINDOW_H
