#ifndef WIREWORLDWIDGET_H
#define WIREWORLDWIDGET_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QGLWidget>
#include <QTimer>
#include <thread>
#include <future>
#include <mutex>
#include "globals.h"
#include "automaton.h"

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

protected:
    void keyPressEvent(QKeyEvent *p_pqkeEvent);
    void mousePressEvent(QMouseEvent *p_qmeEvent);
    void mouseMoveEvent(QMouseEvent *p_qmeEvent);
    void paintEvent(QPaintEvent *);

private slots:
    void update();
    void framesPerSecond();

public:
    WireWorldWidget(QWidget *p_pqwParent = 0);
    ~WireWorldWidget();
    Automaton getAutomaton() const;
    void setAutomaton(const Automaton &p_aAutomaton);
    bool getAutoNextGeneration() const;
    void setAutoNextGeneration(bool p_bAutoNextGeneration);
    void resize(int p_iWidth, int p_iHeight);
    static QColor s_rqcColors[];

};

#endif // WIREWORLDWIDGET_H
