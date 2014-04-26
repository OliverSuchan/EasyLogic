#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
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
    MainWindow(QWidget *p_qwParent = 0);
    MainWindow(int p_iHeight, int p_iWidth, QWidget *p_qwParent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *p_pqrEvent);

private:
    WireWorldWidget *m_pwwwWire;
    Globals::State m_sCurrentState;
};

#endif // MAINWINDOW_H
