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

//void WireWorldWidget::paintEvent(QPaintEvent *p_pqpPaintEvent)
//{
//    m_bCanUpdate = false;
//    if(m_bAutoNextGeneration)
//    {
//        m_bCanUpdate = true;
//        return;
//    }
//    QPainter qpPainter(this);
//    qpPainter.setRenderHint(QPainter::Antialiasing);
//    qreal iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor_X;
//    qreal iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor_Y;
//    for(int iCounterX = 0; iCounterX < m_aAutomaton.getWidth(); iCounterX++)
//    {
//        for(int iCounterY = 0; iCounterY < m_aAutomaton.getHeight(); iCounterY++)
//        {
//            if(iCounterX * iCellWidth <= this->size().width() || iCounterX * iCellHeight <= this->size().height())
//                qpPainter.fillRect(QRectF(iCounterX * iCellWidth, iCounterY * iCellHeight, iCellWidth, iCellHeight), Globals::s_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)]);
//        }
//    }
//    m_bCanUpdate = true;
//}

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
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void WireWorldWidget::resizeGL(int p_iWidth, int p_iHeight)
{
    glClearColor(1.0, 0.0, 0.0, 0.0);
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
    m_bCanUpdate = false;
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_QUADS);
    glClearColor(1.0, 0.0, 0.0, 0.0);
    qreal iCellWidth = Globals::CELL_WIDTH * Globals::ZoomFactor_X;
    qreal iCellHeight = Globals::CELL_HEIGHT * Globals::ZoomFactor_Y;
    for(int iCounterX = 0; iCounterX < m_aAutomaton.getWidth(); iCounterX++)
    {
        for(int iCounterY = 0; iCounterY < m_aAutomaton.getHeight(); iCounterY++)
        {
            if(iCounterX * iCellWidth <= this->size().width() || iCounterX * iCellHeight <= this->size().height())
            {
                QColor color = Globals::s_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)];
                //glColor3d(color.red(),color.blue(),color.green());
                glColor3f(color.red(), 0, 0);
                glRectf(10, 10, 30, 50);
                //glRectf(iCounterX * iCellWidth, 4.0f, 4.0f, 1.0f);
                glVertex2f(0, 0);            //Draw the four corners of the rectangle
                glVertex2f(0, 20);
                glVertex2f(40, 20);
                glVertex2f(40, 0);
            }
            //qpPainter.fillRect(QRectF(iCounterX * iCellWidth, iCounterY * iCellHeight, iCellWidth, iCellHeight), Globals::s_rqcColors[m_aAutomaton.getStateAt(iCounterX, iCounterY)]);
        }
    }
    glEnd();
    glPopMatrix();
    m_bCanUpdate = true;
}

void WireWorldWidget::update()
{
    m_threadMutex.lock();
    if(m_bAutoNextGeneration)
        m_aAutomaton.nextGeneration();
    QMetaObject::invokeMethod(this, "updateGL", Qt::QueuedConnection);
    while(!m_bCanUpdate) {}
    m_iFPS++;
    m_threadMutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    update();
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
    m_sthrUpdateThread = std::thread(&WireWorldWidget::update, this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(framesPerSecond()));
    timer->start(1000);
}

WireWorldWidget::~WireWorldWidget()
{
    m_sthrUpdateThread.join();
}
