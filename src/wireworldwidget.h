#ifndef WIREWORLDWIDGET_H
#define WIREWORLDWIDGET_H

#include <QPaintEvent>
#include <QGLWidget>
#include <QTimer>
#include "globals.h"
#include "automaton.h"

class WireWorldWidget : public QGLWidget
{
    Q_OBJECT

private:
    Automaton m_aAutomaton;
    Globals::State m_sCurrentState;
    bool m_bAuoNextGeneration;

protected:
    void paintEvent(QPaintEvent *p_pqpPaintEvent);
    void keyPressEvent(QKeyEvent *p_pqkeEvent);
    void mousePressEvent(QMouseEvent *p_qmeEvent);
    void mouseMoveEvent(QMouseEvent *p_qmeEvent);

private slots:
    void update();

public:
    WireWorldWidget(QWidget *p_pqwParent = 0);
    Automaton getAutomaton() const;
    void setAutomaton(const Automaton &p_aAutomaton);
    bool getAuoNextGeneration() const;
    void setAuoNextGeneration(bool p_bAuoNextGeneration);
};

#endif // WIREWORLDWIDGET_H
