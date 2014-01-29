#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QEvent>
#include <QKeyEvent>
#include <iostream>
#include "globals.h"
#include "automaton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Automaton m_aAuto;
    Globals::State m_sCurrentState;
};

#endif // MAINWINDOW_H
