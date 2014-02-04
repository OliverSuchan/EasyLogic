#ifndef WIREWORLDWIDGET_H
#define WIREWORLDWIDGET_H

#include <QPaintEvent>
#include <QGLWidget>
#include "globals.h"
#include "automaton.h"

class WireWorldWidget : public QGLWidget
{
    Q_OBJECT

private:
    Automaton m_aAutomaton;
    Globals::State m_sCurrentState;

protected:
    void paintEvent(QPaintEvent *p_pqpPaintEvent);
    void keyPressEvent(QKeyEvent *p_pqkeEvent);
    void mousePressEvent(QMouseEvent *p_qmeEvent);
    void mouseMoveEvent(QMouseEvent *p_qmeEvent);

public:
    WireWorldWidget(QWidget *p_pqwParent = 0);
    Automaton getAutomaton() const;
    void setAutomaton(const Automaton &p_aAutomaton);
};

#endif // WIREWORLDWIDGET_H
