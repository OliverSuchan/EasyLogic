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
    if(m_aAutomaton.getWidth() * Globals::CELL_WIDTH * Globals::ZoomFactor_X != p_iWidth)
        Globals::CELL_WIDTH = p_iWidth / m_aAutomaton.getWidth() + 1;

    if(m_aAutomaton.getHeight() * Globals::CELL_HEIGHT * Globals::ZoomFactor_Y != p_iHeight)
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

void WireWorldWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void WireWorldWidget::resizeGL(int p_iWidth, int p_iHeight)
{   
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, p_iWidth, p_iHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(180, 1.0f, 0, 0);
    glTranslatef(-1.0f, -1.0f, 0);
    glScalef(2.0f/p_iWidth, 2.0f/p_iHeight, 1);

    glTranslatef(2.0f, 2.0f, 0);
}

void WireWorldWidget::paintGL()
{
    m_bCanUpdate.store(false);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    qreal iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor_X;
    qreal iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor_Y;
    for(int iCounterX = 0; iCounterX < m_aAutomaton.getWidth(); iCounterX++)
    {
        for(int iCounterY = 0; iCounterY < m_aAutomaton.getHeight(); iCounterY++)
        {
            if(iCounterX * iCellWidth <= this->size().width() || iCounterX * iCellHeight <= this->size().height())
            {
                QColor color = Globals::s_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)];
                if(color == Qt::black)
                    continue;
                int x1 = iCounterX * iCellWidth;
                int y1 = iCounterY * iCellHeight;
                glColor3f(color.redF(), color.greenF(), color.blueF());
                glVertex2f(x1, y1);
                glVertex2f(x1, y1 + iCellHeight);
                glVertex2f(x1 + iCellWidth, y1 + iCellHeight);
                glVertex2f(x1 + iCellWidth, y1);
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
        QMetaObject::invokeMethod(this, "updateGL", Qt::QueuedConnection);
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
    : QGLWidget(p_pqwParent)
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
