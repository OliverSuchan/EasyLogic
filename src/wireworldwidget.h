#ifndef WIREWORLDWIDGET_H
#define WIREWORLDWIDGET_H

#include <QPaintEvent>
#include <QGLWidget>
#include <QTimer>
#include <thread>
#include <future>
#include <mutex>
#include "globals.h"
#include "automaton.h"

class WireWorldWidget : public QGLWidget
{
    Q_OBJECT

private:
    Automaton m_aAutomaton;
    Globals::State m_sCurrentState;
    bool m_bAutoNextGeneration;
    std::thread m_sthrUpdateThread;
    std::mutex m_threadMutex;
    bool m_bCanUpdate;
    int m_iFPS;

protected:
    //void paintEvent(QPaintEvent *p_pqpPaintEvent);
    void keyPressEvent(QKeyEvent *p_pqkeEvent);
    void mousePressEvent(QMouseEvent *p_qmeEvent);
    void mouseMoveEvent(QMouseEvent *p_qmeEvent);
    void initializeGL();
    void resizeGL(int p_iWidth, int p_iHeight);
    void paintGL();

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

    bool getAuoNextGeneration() const;
    void setAuoNextGeneration(bool p_bAuoNextGeneration);
};

#endif // WIREWORLDWIDGET_H
