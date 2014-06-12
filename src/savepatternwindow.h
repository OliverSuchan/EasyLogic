#ifndef SAVEPATTERNWINDOW_H
#define SAVEPATTERNWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>

class SavePatternWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SavePatternWindow(QWidget *parent = 0);
    QTextEdit *m_pqteNameTextEdit;
    QCheckBox *m_pqcbSelectAllCheckBox;
    QPushButton *m_pqpbSaveButton;
    QPushButton *m_pqpbCancelButton;

protected:
    void closeEvent(QCloseEvent *p_pqceCloseEvent);

signals:
    void closed();

public slots:

};

#endif // SAVEPATTERNWINDOW_H
