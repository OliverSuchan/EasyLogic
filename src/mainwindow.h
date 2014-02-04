#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QEvent>
#include <QKeyEvent>
#include <QtMath>
#include <iostream>
#include "globals.h"
#include "wireworldwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

 protected:
    void resizeEvent(QResizeEvent *p_pqrEvent);

private:
    WireWorldWidget *m_pwwwWire;
    Globals::State m_sCurrentState;
};

#endif // MAINWINDOW_H
