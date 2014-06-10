#include "wireworldwidget.h"

Automaton &WireWorldWidget::getAutomaton()
{
    return m_aAutomaton;
}

void WireWorldWidget::setAutomaton(Automaton p_aAutomaton)
{
    m_aAutomaton = p_aAutomaton;
}


bool WireWorldWidget::getAutoNextGeneration() const
{
    return m_bAutoNextGeneration;
}

void WireWorldWidget::setAutoNextGeneration(bool p_bAutoNextGeneration)
{
    m_bAutoNextGeneration = p_bAutoNextGeneration;
}

void WireWorldWidget::resize(int p_iWidth, int p_iHeight)
{
    QWidget::resize(p_iWidth, p_iHeight);
    if(m_aAutomaton.getWidth() * Globals::getInstance().m_dCellWidth * Globals::getInstance().m_dZoomFactor != p_iWidth)
        Globals::getInstance().m_dCellWidth = p_iWidth / m_aAutomaton.getWidth() + 1;

    if(m_aAutomaton.getHeight() * Globals::getInstance().m_dCellHeight * Globals::getInstance().m_dZoomFactor != p_iHeight)
        Globals::getInstance().m_dCellHeight = p_iHeight / m_aAutomaton.getHeight() + 1;
}

void WireWorldWidget::setCurrentState(Globals::State p_sNewState)
{
    m_sCurrentState = p_sNewState;
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
        this->setAutoNextGeneration(!this->getAutoNextGeneration());
    }
    else if(p_pqkeEvent->key() == Qt::Key_Plus)
    {
        Globals::getInstance().m_dZoomFactor += 0.1;
    }
    else if(p_pqkeEvent->key() == Qt::Key_Minus)
    {
        Globals::getInstance().m_dZoomFactor -= 0.1;
    }
    else if(p_pqkeEvent->key() == Qt::Key_NumberSign)
    {
        Globals::getInstance().m_dZoomFactor = 1;
    }
}

void WireWorldWidget::mousePressEvent(QMouseEvent *p_qmeEvent)
{
    if(p_qmeEvent->button() == Qt::LeftButton)
    {
        double iX = p_qmeEvent->windowPos().x() - Globals::getInstance().m_iX;
        double iY = p_qmeEvent->windowPos().y() - Globals::getInstance().m_iY;
        double iCellWidth = Globals::getInstance().m_dCellWidth * Globals::getInstance().m_dZoomFactor;
        double iCellHeight = Globals::getInstance().m_dCellHeight * Globals::getInstance().m_dZoomFactor;
        int iCellNumberAbscissa = static_cast<int>(iX / iCellWidth);
        int iCellNumberOrdinant = static_cast<int>(iY / iCellHeight);
        try
        {
            m_aAutomaton.setCellState(m_sCurrentState, iCellNumberAbscissa, iCellNumberOrdinant);
        }
        catch(std::exception) {}
    }
    m_qpOldMousePosition = p_qmeEvent->pos();
}

void WireWorldWidget::mouseMoveEvent(QMouseEvent *p_qmeEvent)
{
    if(p_qmeEvent->buttons() == Qt::LeftButton)
    {
        double iX = p_qmeEvent->windowPos().x() - Globals::getInstance().m_iX;
        double iY = p_qmeEvent->windowPos().y() - Globals::getInstance().m_iY;
        double iCellWidth = Globals::getInstance().m_dCellWidth * Globals::getInstance().m_dZoomFactor;
        double iCellHeight = Globals::getInstance().m_dCellHeight * Globals::getInstance().m_dZoomFactor;
        int iCellNumberAbscissa = static_cast<int>(iX / iCellWidth);
        int iCellNumberOrdinant = static_cast<int>(iY / iCellHeight);
        try
        {
            m_aAutomaton.setCellState(m_sCurrentState, iCellNumberAbscissa, iCellNumberOrdinant);
        }
        catch(std::exception) {}
    }
    else if(p_qmeEvent->buttons() == Qt::MidButton)
    {
        Globals::getInstance().m_iX += p_qmeEvent->pos().x() - m_qpOldMousePosition.x();
        Globals::getInstance().m_iY += p_qmeEvent->pos().y() - m_qpOldMousePosition.y();
    }
    m_qpOldMousePosition = p_qmeEvent->pos();
}

void WireWorldWidget::paintEvent(QPaintEvent *)
{
    m_bCanUpdate.store(false);
    QPainter qpPainter(this);
    qpPainter.setRenderHint(QPainter::HighQualityAntialiasing);
    qpPainter.fillRect(0, 0, size().width(), size().height(), Globals::getInstance().m_rqcColors[Globals::getInstance().EMPTY]);
    double dCellWidth = Globals::getInstance().m_dCellWidth * Globals::getInstance().m_dZoomFactor;
    double dCellHeight = Globals::getInstance().m_dCellHeight * Globals::getInstance().m_dZoomFactor;
    for(int iCounterX = 0; iCounterX < m_aAutomaton.getWidth(); iCounterX++)
    {
        for(int iCounterY = 0; iCounterY < m_aAutomaton.getHeight(); iCounterY++)
        {
            if(Globals::getInstance().m_iX + iCounterX * dCellWidth <= this->size().width() || Globals::getInstance().m_iY + iCounterX * dCellHeight <= this->size().height())
            {
                QColor color = Globals::getInstance().m_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)];
                if(color == Globals::getInstance().m_rqcColors[Globals::getInstance().EMPTY])
                    continue;
                qpPainter.fillRect(QRectF(Globals::getInstance().m_iX + iCounterX * dCellWidth, Globals::getInstance().m_iY + iCounterY * dCellHeight, dCellWidth, dCellHeight), color);
            }
        }
    }
    m_bCanUpdate.store(true);
}

void WireWorldWidget::wheelEvent(QWheelEvent *p_pqweWheelEvent)
{
    int numDegrees = p_pqweWheelEvent->delta() / 8;
    int numSteps = numDegrees;
    if (p_pqweWheelEvent->orientation() == Qt::Horizontal)
    {
        Globals::getInstance().m_iX += numSteps;
    }
    else
    {
        Globals::getInstance().m_iY += numSteps;
    }
}


void WireWorldWidget::update()
{
    while(true)
    {
        m_threadMutex.lock();
        if(m_bAutoNextGeneration.load())
            m_aAutomaton.nextGeneration();
        m_threadMutex.unlock();
        QMetaObject::invokeMethod(this, "repaint", Qt::QueuedConnection);
        while(!m_bCanUpdate.load()) {}
        m_iFPS.store(m_iFPS.load() + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void WireWorldWidget::framesPerSecond()
{
    m_threadMutex.lock();
    std::cout << "Frames per Second: " << m_iFPS.load() << std::endl;
    m_iFPS.store(0);
    m_threadMutex.unlock();
}

WireWorldWidget::WireWorldWidget(QWidget *p_pqwParent)
    : QWidget(p_pqwParent)
{
    setFocusPolicy(Qt::ClickFocus);
    m_bAutoNextGeneration.store(false);
    m_bCanUpdate.store(false);
    m_iFPS.store(0);
    m_sthrUpdateThread = new std::thread(&WireWorldWidget::update, this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(framesPerSecond()));
    timer->start(1000);
}

WireWorldWidget::~WireWorldWidget()
{
    m_sthrUpdateThread->join();
}
