#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_sCurrentState = Globals::EMPTY;
    m_pwwwWire = new WireWorldWidget(this);
    m_pwwwWire->show();
    m_pwwwWire->setAutomaton(Automaton(20, 20));
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
