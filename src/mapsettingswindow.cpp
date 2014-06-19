#include "mapsettingswindow.h"

MapSettingsWindow::MapSettingsWindow(QWidget *parent)
    : QMainWindow(parent),
      m_pqcdColorPicker(0)
{
    this->resize(220, 0);
    m_pqsbWidthSpinBox = new QSpinBox(this);
    m_pqsbWidthSpinBox->setGeometry(20, 20, 75, 25);
    m_pqsbWidthSpinBox->setMinimum(1);
    m_pqsbWidthSpinBox->setMaximum(std::numeric_limits<int>::max());
    m_pqsbWidthSpinBox->show();
    std::cout << std::numeric_limits<int>::max() << std::endl;

    m_pqsbHeightSpinBox = new QSpinBox(this);
    m_pqsbHeightSpinBox->setGeometry(125, 20, 75, 25);
    m_pqsbHeightSpinBox->setMinimum(1);
    m_pqsbHeightSpinBox->setMaximum(std::numeric_limits<int>::max());
    m_pqsbHeightSpinBox->show();

    m_pqlblProductLabel = new QLabel(this);
    m_pqlblProductLabel->setGeometry(107, 20, 10, 25);
    m_pqlblProductLabel->setStyleSheet("color: rgb(255, 255, 255);");
    m_pqlblProductLabel->setText("x");
    m_pqlblProductLabel->show();

    int iY = 60;
    for(int iIndex = 0; iIndex < 4; iIndex++)
    {
        QLabel *pqlblStateName = new QLabel(this);
        pqlblStateName->setGeometry(20, iY, 120, 25);
        pqlblStateName->setStyleSheet("color: rgb(255, 255, 255);");
        pqlblStateName->setText(Globals::getInstance().m_rqstStateNames[iIndex] + ":");
        pqlblStateName->show();

        QPushButton *pqfColorPickerButton = new QPushButton(this);
        pqfColorPickerButton->setFlat(true);
        pqfColorPickerButton->setGeometry(size().width() - 36, iY + 5, 16, 16);
        pqfColorPickerButton->show();
        pqfColorPickerButton->setStyleSheet("QPushButton:flat { border: 1px solid white; background-color: " + Globals::getInstance().m_rqcColors[iIndex].name() + "; }");
        pqfColorPickerButton->show();
        connect(pqfColorPickerButton, &QPushButton::clicked, this, [=]() {
            changeColor(iIndex, pqfColorPickerButton);
        });
        iY += 40;
    }

    this->resize(220, iY + 65);

    m_pqpbApplyButton = new QPushButton(this);
    m_pqpbApplyButton->setGeometry(20, size().height() - 40, 180, 25);
    this->move((QApplication::desktop()->width() - this->size().width()) / 2, (QApplication::desktop()->height() - this->size().height()) / 2);
    connect(m_pqpbApplyButton, SIGNAL(clicked()), this, SLOT(applyButtonClickEvent()));
    m_pqpbApplyButton->setText("Anwenden");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(500);
}

void MapSettingsWindow::paintEvent(QPaintEvent *)
{
    QPainter qpPainter(this);
    qpPainter.setRenderHint(QPainter::HighQualityAntialiasing);
    qpPainter.fillRect(0, 0, size().width(), size().height(), Qt::black);
    qreal qrCellHeight = 8;
    qreal qrCellWidth = 8;
    for(int iX = 0; iX < size().width(); iX += qrCellHeight)
    {
        for(int iY = 0; iY < size().height(); iY += qrCellWidth)
        {
            int iRandomNumber = qrand() % 20;
            qpPainter.fillRect(iX, iY, qrCellHeight, qrCellWidth, QColor(iRandomNumber, iRandomNumber, iRandomNumber));
        }
    }

}

void MapSettingsWindow::applyButtonClickEvent()
{
    MainWindow *pmwMainGUI = new MainWindow(m_pqsbHeightSpinBox->value(), m_pqsbWidthSpinBox->value());
    pmwMainGUI->show();
    this->close();
}

void MapSettingsWindow::changeColor(int p_iIndex, QPushButton *p_pqpbPushButton)
{
    if(!m_pqcdColorPicker)
        m_pqcdColorPicker = new QColorDialog(this);
    else
    {
        m_pqcdColorPicker->close();
        m_pqcdColorPicker = NULL;
        delete m_pqcdColorPicker;
        changeColor(p_iIndex, p_pqpbPushButton);
        return;
    }
    m_pqcdColorPicker->setCurrentColor(Globals::getInstance().m_rqcColors[p_iIndex]);
    m_pqcdColorPicker->show();
    connect(m_pqcdColorPicker, &QColorDialog::accepted, [=]() {
        Globals::getInstance().m_rqcColors[p_iIndex] = m_pqcdColorPicker->currentColor();
        p_pqpbPushButton->setStyleSheet("QPushButton:flat { border: 1px solid white; background-color: " + Globals::getInstance().m_rqcColors[p_iIndex].name() + "; }");
    });

}
