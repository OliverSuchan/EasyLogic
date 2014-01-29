#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(753, 411);
    this->installEventFilter(this);
    m_sCurrentState = Globals::EMPTY;
    m_aAuto = Automaton(3,3);
    std::cout << "0: Empty" << std::endl;
    std::cout << "1: Conductor" << std::endl;
    std::cout << "2: Head" << std::endl;
    std::cout << "3: Tail" << std::endl;
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pPainter(this);
    int iCellWidth = (width() - m_aAuto.getWidth() + 1) / m_aAuto.getWidth();
    int iCellHeight = (height() - m_aAuto.getHeight() + 1) / m_aAuto.getHeight();
    for(int iCounterX = 0; iCounterX < m_aAuto.getWidth(); iCounterX++)
    {
        for(int iCounterY = 0; iCounterY < m_aAuto.getHeight(); iCounterY++)
        {
            QColor qcCellColor;
            switch(m_aAuto.getStateAt(iCounterX, iCounterY))
            {
            case Globals::CONDUCTOR: qcCellColor = QColor(Qt::yellow);
                break;
            case Globals::HEAD: qcCellColor = QColor(Qt::blue);
                break;
            case Globals::TAIL: qcCellColor = QColor(Qt::red);
                break;
            default: qcCellColor = QColor(Qt::black);
            }
            pPainter.fillRect(1*iCounterX+iCounterX*iCellWidth,1*iCounterY+iCounterY*iCellHeight,iCellWidth,iCellHeight, qcCellColor);
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *qkEvent = static_cast<QKeyEvent *>(event);
        if(qkEvent->key() >= Qt::Key_0 && qkEvent->key() <= Qt::Key_3)
        {
            m_sCurrentState = static_cast<Globals::State>(qkEvent->key() - 48);
            return true;
        }
        else if(qkEvent->key() == Qt::Key_Return)
        {
            std::cout << "Current Generation: " << m_aAuto.nextGeneration() << std::endl;
            this->repaint();
            return true;
        }
        return QObject::eventFilter(obj, event);
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *qmEvent = static_cast<QMouseEvent*>(event);
        if(qmEvent->button() == Qt::LeftButton)
        {
            int iX = qmEvent->windowPos().x();
            int iY = qmEvent->windowPos().y();
            int iCellWidth = (width() - m_aAuto.getWidth() + 1) / m_aAuto.getWidth();
            int iCellHeight = (height() - m_aAuto.getHeight() + 1) / m_aAuto.getHeight();
            int iCellNumberAbscissa = iX / iCellWidth;
            int iCellNumberOrdinant = iY / iCellHeight;
            m_aAuto.setCellState(m_sCurrentState, iCellNumberAbscissa, iCellNumberOrdinant);
            this->repaint();
        }
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}
