#ifndef WIREWORLDWIDGET_H
#define WIREWORLDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QPoint>
#include <thread>
#include <future>
#include <mutex>
#include "globals.h"
#include "automaton.h"
#include "dataio.h"

class WireWorldWidget : public QWidget
{
    Q_OBJECT

private:
    Automaton m_aAutomaton;
    Globals::State m_sCurrentState;
    std::atomic<bool> m_bAutoNextGeneration;
    std::thread *m_sthrUpdateThread;
    std::mutex m_threadMutex;
    std::atomic<bool> m_bCanUpdate;
    std::atomic<int> m_iFPS;
    QPoint m_qpOldMousePosition;

protected:
    void keyPressEvent(QKeyEvent *p_pqkeEvent);
    void mousePressEvent(QMouseEvent *p_qmeEvent);
    void mouseMoveEvent(QMouseEvent *p_qmeEvent);
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *p_pqweWheelEvent);

private slots:
    void update();
    void framesPerSecond();

public:
    WireWorldWidget(QWidget *p_pqwParent = 0);
    ~WireWorldWidget();
    Automaton &getAutomaton();
    void setAutomaton(Automaton p_aAutomaton);
    bool getAutoNextGeneration() const;
    void setAutoNextGeneration(bool p_bAutoNextGeneration);
    void resize(int p_iWidth, int p_iHeight);
    void setCurrentState(Globals::State p_sNewState);

};

#endif // WIREWORLDWIDGET_H
