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
    if(m_aAutomaton.getWidth() * Globals::CELL_WIDTH * Globals::ZoomFactor != p_iWidth)
        Globals::CELL_WIDTH = p_iWidth / m_aAutomaton.getWidth() + 1;

    if(m_aAutomaton.getHeight() * Globals::CELL_HEIGHT * Globals::ZoomFactor != p_iHeight)
        Globals::CELL_HEIGHT = p_iHeight / m_aAutomaton.getHeight() + 1;
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
        Globals::ZoomFactor += 0.1;
    }
    else if(p_pqkeEvent->key() == Qt::Key_Minus)
    {
        Globals::ZoomFactor -= 0.1;
    }
    else if(p_pqkeEvent->key() == Qt::Key_NumberSign)
    {
        Globals::ZoomFactor = 1;
    }
}

void WireWorldWidget::mousePressEvent(QMouseEvent *p_qmeEvent)
{
    if(p_qmeEvent->button() == Qt::LeftButton)
    {
        double iX = p_qmeEvent->windowPos().x();
        double iY = p_qmeEvent->windowPos().y();
        double iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor;
        double iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor;
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
    double iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor;
    double iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor;
    int iCellNumberAbscissa = static_cast<int>(iX / iCellWidth);
    int iCellNumberOrdinant = static_cast<int>(iY / iCellHeight);
    try
    {
        m_aAutomaton.setCellState(m_sCurrentState, iCellNumberAbscissa, iCellNumberOrdinant);
    }
    catch(std::exception) {}
}

void WireWorldWidget::paintEvent(QPaintEvent *)
{
    m_bCanUpdate.store(false);
    QPainter qpPainter(this);
    qpPainter.setRenderHint(QPainter::HighQualityAntialiasing);
    qpPainter.fillRect(0, 0, size().height(), size().width(), Globals::s_rqcColors[Globals::EMPTY]);
    qreal iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor;
    qreal iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor;
    for(int iCounterX = 0; iCounterX < m_aAutomaton.getWidth(); iCounterX++)
    {
        for(int iCounterY = 0; iCounterY < m_aAutomaton.getHeight(); iCounterY++)
        {
            if(iCounterX * iCellWidth <= this->size().width() || iCounterX * iCellHeight <= this->size().height())
            {
                QColor color = Globals::s_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)];
                if(color == Qt::black)
                    continue;
                qpPainter.fillRect(QRectF(iCounterX * iCellWidth, iCounterY * iCellHeight, iCellWidth, iCellHeight), color);
            }
        }
    }
    glEnd();
    m_bCanUpdate.store(true);
}

void WireWorldWidget::update()
{
    while(true)
    {
        m_threadMutex.lock();
        if(m_bAutoNextGeneration)
            m_aAutomaton.nextGeneration();
        QMetaObject::invokeMethod(this, "repaint", Qt::QueuedConnection);
        while(!m_bCanUpdate.load()) {}
        m_iFPS++;
        m_threadMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void WireWorldWidget::framesPerSecond()
{
    m_threadMutex.lock();
    std::cout << "Frames per Second: " << m_iFPS << std::endl;
    m_iFPS = 0;
    m_threadMutex.unlock();
}

WireWorldWidget::WireWorldWidget(QWidget *p_pqwParent)
    : QWidget(p_pqwParent)
{
    setFocusPolicy(Qt::ClickFocus);
    m_bAutoNextGeneration.store(false);
    m_bCanUpdate.store(false);
    m_sthrUpdateThread = new std::thread(&WireWorldWidget::update, this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(framesPerSecond()));
    timer->start(1000);
}

WireWorldWidget::~WireWorldWidget()
{
    m_sthrUpdateThread->join();
}
