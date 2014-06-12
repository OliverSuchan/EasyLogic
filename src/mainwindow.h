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
    QMenu *m_pqmPatternsMenu;
    QAction *m_pqaEmptyState;
    QAction *m_pqaConductorState;
    QAction *m_pqaHeadState;
    QAction *m_pqaTailState;
    void setupUI();
    void init();

private slots:
    void itemTriggeredAction();
    void reloadPatternList();
};

#endif // MAINWINDOW_H
