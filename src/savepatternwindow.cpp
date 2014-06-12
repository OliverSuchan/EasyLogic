#include "savepatternwindow.h"

SavePatternWindow::SavePatternWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Tool)
{
    this->resize(300, 100);
    this->move((QApplication::desktop()->width() - this->size().width()) / 2, (QApplication::desktop()->height() - this->size().height()) / 2);
    this->setFixedSize(this->size());

    m_pqteNameTextEdit = new QTextEdit(this);
    m_pqteNameTextEdit->setGeometry(10, 10, this->size().width() - 20, 25);
    m_pqteNameTextEdit->setPlaceholderText("Pattern-Name");

    m_pqcbSelectAllCheckBox = new QCheckBox("Alles auswählen", this);
    m_pqcbSelectAllCheckBox->setGeometry(10, m_pqteNameTextEdit->y() + m_pqteNameTextEdit->size().height(), m_pqcbSelectAllCheckBox->size().width(), m_pqcbSelectAllCheckBox->size().height());

    m_pqpbSaveButton = new QPushButton("Speichern", this);
    m_pqpbSaveButton->setGeometry(10, m_pqcbSelectAllCheckBox->y() + m_pqcbSelectAllCheckBox->size().height(), 135, 25);

    m_pqpbCancelButton = new QPushButton("Abbrechen", this);
    m_pqpbCancelButton->setGeometry(m_pqpbSaveButton->x() + m_pqpbSaveButton->size().width() + 10, m_pqcbSelectAllCheckBox->y() + m_pqcbSelectAllCheckBox->size().height(), 135, 25);
    connect(m_pqpbCancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void SavePatternWindow::closeEvent(QCloseEvent *p_pqceCloseEvent)
{
    emit closed();
}

void closed()
{

}
