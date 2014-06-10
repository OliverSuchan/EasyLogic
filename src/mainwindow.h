#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
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
#include <iostream>
#include <limits>
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
    void paintEvent(QPaintEvent *p_pqpePaintEvent);

private:
    WireWorldWidget *m_pwwwWire;
    Globals::State m_sCurrentState;
    QPushButton *m_pqpbStartButton;
    QPushButton *m_pqpbStopButton;
    QPushButton *m_pqpbSaveButton;
    QPushButton *m_pqpbNextStepButton;
    QPushButton *m_pqpbPreviousStepButton;
    QSpinBox *m_pqsbStepBox;
    QSlider *m_pqsZoomSlider;
    QMenuBar *m_pqmbMenuBar;
    QMenu *m_pqmItemsMenu;
    QAction *m_pqaEmptyState;
    QAction *m_pqaConductorState;
    QAction *m_pqaHeadState;
    QAction *m_pqaTailState;
    void setupUI();
    void init();

private slots:
    void itemTriggeredAction();
};

#endif // MAINWINDOW_H
