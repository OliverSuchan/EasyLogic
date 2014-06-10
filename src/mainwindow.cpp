#include "mainwindow.h"

MainWindow::MainWindow(QWidget *p_qwParent)
    : QMainWindow(p_qwParent)
{
   init();
}

MainWindow::MainWindow(int p_iHeight, int p_iWidth, QWidget *p_qwParent)
    : QMainWindow(p_qwParent)
{
    init();
    m_pwwwWire->setAutomaton(Automaton(p_iHeight, p_iWidth));
}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent *p_pqrEvent)
{
    this->m_pwwwWire->resize(p_pqrEvent->size().width() - 100, p_pqrEvent->size().height());
    m_pqpbStartButton->setGeometry(p_pqrEvent->size().width() - 90, 20 + m_pqmbMenuBar->height(), 80, 25);
    m_pqpbStopButton->setGeometry(p_pqrEvent->size().width() - 90, 50 + m_pqmbMenuBar->height(), 80, 25);
    m_pqpbSaveButton->setGeometry(p_pqrEvent->size().width() - 90, 80 + m_pqmbMenuBar->height(), 80, 25);
    m_pqpbNextStepButton->setGeometry(p_pqrEvent->size().width() - 90, 110 + m_pqmbMenuBar->height(), 80, 25);
    m_pqpbPreviousStepButton->setGeometry(p_pqrEvent->size().width() - 90, 140 + m_pqmbMenuBar->height(), 80, 25);
    m_pqsbStepBox->setGeometry(p_pqrEvent->size().width() - 90, 170 + m_pqmbMenuBar->height(), 80, 25);
    m_pqsZoomSlider->setGeometry(p_pqrEvent->size().width() - 74, 200 + m_pqmbMenuBar->height(), 50, 120);
    this->setMinimumSize(410, 340 + m_pqmbMenuBar->height());
}

void MainWindow::paintEvent(QPaintEvent *p_pqpePaintEvent)
{
    if(m_pqpbStartButton && m_pqpbStopButton)
    {
        m_pqpbStartButton->setEnabled(!this->m_pwwwWire->getAutoNextGeneration());
        m_pqpbStopButton->setEnabled(this->m_pwwwWire->getAutoNextGeneration());
    }

    if(m_pqpbPreviousStepButton)
        m_pqpbPreviousStepButton->setEnabled(this->m_pwwwWire->getAutomaton().canGeneratePreviousGeneration());
}

void MainWindow::setupUI()
{
    m_pqpbStartButton = new QPushButton(this);
    m_pqpbStartButton->setText("Start");
    connect(m_pqpbStartButton, &QPushButton::clicked, [=](){
        this->m_pwwwWire->setAutoNextGeneration(true);
    });
    m_pqpbStartButton->show();

    m_pqpbStopButton = new QPushButton(this);
    m_pqpbStopButton->setText("Stop");
    connect(m_pqpbStopButton, &QPushButton::clicked, [=](){
        this->m_pwwwWire->setAutoNextGeneration(false);
    });
    m_pqpbStopButton->show();

    m_pqpbSaveButton = new QPushButton(this);
    m_pqpbSaveButton->setText("Save");
    connect(m_pqpbSaveButton, &QPushButton::clicked, [=](){
        this->m_pwwwWire->getAutomaton().setGenerationArray();
    });
    m_pqpbSaveButton->show();

    m_pqpbNextStepButton = new QPushButton(this);
    m_pqpbNextStepButton->setText("Next");
    connect(m_pqpbNextStepButton, &QPushButton::clicked, [=](){
        this->m_pwwwWire->getAutomaton().nextGeneration(m_pqsbStepBox->value());
    });
    m_pqpbNextStepButton->show();

    m_pqpbPreviousStepButton = new QPushButton(this);
    m_pqpbPreviousStepButton->setText("Prev");
    connect(m_pqpbPreviousStepButton, &QPushButton::clicked, [=](){
        this->m_pwwwWire->getAutomaton().previousGeneration(m_pqsbStepBox->value());
    });
    m_pqpbPreviousStepButton->show();

    m_pqsbStepBox = new QSpinBox(this);
    m_pqsbStepBox->setMinimum(1);
    m_pqsbStepBox->setMaximum(std::numeric_limits<int>::max());
    m_pqsbStepBox->show();

    m_pqsZoomSlider = new QSlider(this);
    m_pqsZoomSlider->setOrientation(Qt::Vertical);
    m_pqsZoomSlider->setSingleStep(10);
    m_pqsZoomSlider->setPageStep(50);
    m_pqsZoomSlider->setMaximum(250);
    m_pqsZoomSlider->setMinimum(10);
    m_pqsZoomSlider->setValue(100);
    m_pqsZoomSlider->setTickPosition(QSlider::TicksBothSides);
    m_pqsZoomSlider->show();
    connect(m_pqsZoomSlider, &QSlider::valueChanged, [=](){
        Globals::getInstance().m_dZoomFactor = m_pqsZoomSlider->value() / 100.0;
    });

    m_pqmbMenuBar = new QMenuBar(this);
    m_pqmItemsMenu = new QMenu(m_pqmbMenuBar);
    m_pqmbMenuBar->show();
    this->setMenuBar(m_pqmbMenuBar);
    connect(m_pqmItemsMenu->menuAction(), SIGNAL(triggered()), this, SLOT(itemTriggeredAction()));
    m_pqaEmptyState = new QAction(m_pqmItemsMenu);
    connect(m_pqaEmptyState, &QAction::triggered, [=]() {
        this->m_pwwwWire->setCurrentState(Globals::EMPTY);
    });

    m_pqaConductorState = new QAction(m_pqmItemsMenu);
    connect(m_pqaConductorState, &QAction::triggered, [=]() {
        this->m_pwwwWire->setCurrentState(Globals::CONDUCTOR);
    });

    m_pqaHeadState = new QAction(m_pqmItemsMenu);
    connect(m_pqaHeadState, &QAction::triggered, [=]() {
        this->m_pwwwWire->setCurrentState(Globals::HEAD);
    });

    m_pqaTailState = new QAction(m_pqmItemsMenu);
    connect(m_pqaTailState, &QAction::triggered, [=]() {
        this->m_pwwwWire->setCurrentState(Globals::TAIL);
    });
    m_pqmbMenuBar->addAction(m_pqmItemsMenu->menuAction());
    m_pqmItemsMenu->setTitle("Elemente");
    m_pqmItemsMenu->addAction(m_pqaEmptyState);
    m_pqmItemsMenu->addAction(m_pqaConductorState);
    m_pqmItemsMenu->addAction(m_pqaHeadState);
    m_pqmItemsMenu->addAction(m_pqaTailState);
    itemTriggeredAction();
}

void MainWindow::init()
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
    this->setupUI();
}

void MainWindow::itemTriggeredAction()
{
    m_pqaEmptyState->setText(Globals::getInstance().m_rqstStateNames[Globals::EMPTY]);
    QPixmap qpmEmptyStateImage(32, 32);
    qpmEmptyStateImage.fill(Globals::getInstance().m_rqcColors[Globals::EMPTY]);
    m_pqaEmptyState->setIcon(QIcon(qpmEmptyStateImage));

    m_pqaConductorState->setText(Globals::getInstance().m_rqstStateNames[Globals::CONDUCTOR]);
    QPixmap qpmConductorStateImage(32, 32);
    qpmConductorStateImage.fill(Globals::getInstance().m_rqcColors[Globals::CONDUCTOR]);
    m_pqaConductorState->setIcon(QIcon(qpmConductorStateImage));

    m_pqaHeadState->setText(Globals::getInstance().m_rqstStateNames[Globals::HEAD]);
    QPixmap qpHeadStateImage(32, 32);
    qpHeadStateImage.fill(Globals::getInstance().m_rqcColors[Globals::HEAD]);
    m_pqaHeadState->setIcon(QIcon(qpHeadStateImage));

    m_pqaTailState->setText(Globals::getInstance().m_rqstStateNames[Globals::TAIL]);
    QPixmap qpmTailStateImage(32, 32);
    qpmTailStateImage.fill(Globals::getInstance().m_rqcColors[Globals::TAIL]);
    m_pqaTailState->setIcon(QIcon(qpmTailStateImage));
}
