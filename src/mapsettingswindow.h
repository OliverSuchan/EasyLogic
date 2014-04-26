#ifndef MAPSETTINGSWINDOW_H
#define MAPSETTINGSWINDOW_H

#include <QMainWindow>
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

class MapSettingsWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapSettingsWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void applyButtonClickEvent();
    void changeColor(int p_iIndex, QPushButton *p_pqpbPushButton);

private:
    QSpinBox *m_pqsbWidthSpinBox;
    QSpinBox *m_pqsbHeightSpinBox;
    QPushButton *m_pqpbApplyButton;
    QColorDialog *m_pqcdColorPicker;
    QLabel *m_pqlblProductLabel;

};

#endif // MAPSETTINGSWINDOW_H
