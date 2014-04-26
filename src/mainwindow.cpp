#include "mainwindow.h"

MainWindow::MainWindow(QWidget *p_qwParent)
    : QMainWindow(p_qwParent)
{
    m_sCurrentState = Globals::EMPTY;
    m_pwwwWire = new WireWorldWidget(this);
    m_pwwwWire->show();
    m_pwwwWire->setAutomaton(Automaton(200, 200));
    m_pwwwWire->setFocus();
    this->resize(700, 700);
    std::cout << "0: Empty" << std::endl;
    std::cout << "1: Conductor" << std::endl;
    std::cout << "2: Head" << std::endl;
    std::cout << "3: Tail" << std::endl;
}

MainWindow::MainWindow(int p_iHeight, int p_iWidth, QWidget *p_qwParent)
    : QMainWindow(p_qwParent)
{
    m_sCurrentState = Globals::EMPTY;
    m_pwwwWire = new WireWorldWidget(this);
    m_pwwwWire->show();
    m_pwwwWire->setAutomaton(Automaton(p_iHeight, p_iWidth));
    m_pwwwWire->setFocus();
    this->resize(700, 700);
    std::cout << "0: Empty" << std::endl;
    std::cout << "1: Conductor" << std::endl;
    std::cout << "2: Head" << std::endl;
    std::cout << "3: Tail" << std::endl;
}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent *p_pqrEvent)
{
    this->m_pwwwWire->resize(p_pqrEvent->size().width(), p_pqrEvent->size().height());
}
