#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_aAuto= Automaton(50,50);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pPainter(this);
    int iCellWidth = width()/m_aAuto.getWidth();
    int iCellHeight = height()/m_aAuto.getWidth();
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

           pPainter.fillRect
                  (
                  iCounterX*iCellWidth,iCounterY*iCellHeight,iCellWidth,iCellHeight, qcCellColor
                  );
       }
   }
}
