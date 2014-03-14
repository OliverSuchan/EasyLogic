#include "wireworldwidget.h"


Automaton WireWorldWidget::getAutomaton() const
{
    return m_aAutomaton;
}

void WireWorldWidget::setAutomaton(const Automaton &p_aAutomaton)
{
    m_aAutomaton = p_aAutomaton;
    this->repaint();
}


bool WireWorldWidget::getAuoNextGeneration() const
{
    return m_bAuoNextGeneration;
}

void WireWorldWidget::setAuoNextGeneration(bool p_bAuoNextGeneration)
{
    m_bAuoNextGeneration = p_bAuoNextGeneration;
}
void WireWorldWidget::paintEvent(QPaintEvent *p_pqpPaintEvent)
{
    QPainter qpPainter(this);
    qpPainter.setRenderHint(QPainter::Antialiasing);
    qreal iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor_X;
    qreal iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor_Y;
    for(int iCounterX = 0; iCounterX < m_aAutomaton.getWidth(); iCounterX++)
    {
        for(int iCounterY = 0; iCounterY < m_aAutomaton.getHeight(); iCounterY++)
        {
            if(iCounterX * iCellWidth <= this->size().width() || iCounterX * iCellHeight <= this->size().height())
                qpPainter.fillRect(QRectF(iCounterX * iCellWidth, iCounterY * iCellHeight, iCellWidth, iCellHeight), Globals::s_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)]);
        }
    }
}

void WireWorldWidget::keyPressEvent(QKeyEvent *p_pqkeEvent)
{
    if(p_pqkeEvent->key() >= Qt::Key_0 && p_pqkeEvent->key() <= Qt::Key_3)
    {
        m_sCurrentState = static_cast<Globals::State>(p_pqkeEvent->key() - 48);
        std::cout << "Changed State" << std::endl;
    }
    else if(p_pqkeEvent->key() == Qt::Key_Return)
    {
        std::cout << "Current Generation: " << m_aAutomaton.nextGeneration() << std::endl;
    }
    else if(p_pqkeEvent->key() == Qt::Key_Space)
    {
        this->setAuoNextGeneration(!this->getAuoNextGeneration());
    }
    else if(p_pqkeEvent->key() == Qt::Key_Plus)
    {
        Globals::ZoomFactor_X += 0.1;
        Globals::ZoomFactor_Y += 0.1;
    }
    else if(p_pqkeEvent->key() == Qt::Key_Minus)
    {
        Globals::ZoomFactor_X -= 0.1;
        Globals::ZoomFactor_Y -= 0.1;
    }
}

void WireWorldWidget::mousePressEvent(QMouseEvent *p_qmeEvent)
{
    if(p_qmeEvent->button() == Qt::LeftButton)
    {
        double iX = p_qmeEvent->windowPos().x();
        double iY = p_qmeEvent->windowPos().y();
        double iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor_X;
        double iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor_Y;
        int iCellNumberAbscissa = static_cast<int>(iX / iCellWidth);
        int iCellNumberOrdinant = static_cast<int>(iY / iCellHeight);
        try
        {
            m_aAutomaton.setCellState(m_sCurrentState, iCellNumberAbscissa, iCellNumberOrdinant);
        }
        catch(std::exception) {}
    }
}

void WireWorldWidget::mouseMoveEvent(QMouseEvent *p_qmeEvent)
{
    double iX = p_qmeEvent->windowPos().x();
    double iY = p_qmeEvent->windowPos().y();
    double iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor_X;
    double iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor_Y;
    int iCellNumberAbscissa = static_cast<int>(iX / iCellWidth);
    int iCellNumberOrdinant = static_cast<int>(iY / iCellHeight);
    try
    {
        m_aAutomaton.setCellState(m_sCurrentState, iCellNumberAbscissa, iCellNumberOrdinant);
    }
    catch(std::exception) {}
}

void WireWorldWidget::update()
{
    this->repaint();
    if(m_bAuoNextGeneration)
        m_aAutomaton.nextGeneration();
}

WireWorldWidget::WireWorldWidget(QWidget *p_pqwParent)
    : QWidget(p_pqwParent)
{
    setFocusPolicy(Qt::ClickFocus);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}
