#include "statusbuttonbar.h"

#include "statusbuttonbar.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QTimer>


StatusButtonBar::StatusButtonBar(QWidget *parent)
    : QWidget(parent)
{
    m_label = new QLabel;
    m_label->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
    m_checkBox = new QCheckBox(tr("&Show Images"));
    m_buttonBox = new QDialogButtonBox;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_label, 1);
    layout->addWidget(m_checkBox);
    layout->addWidget(m_buttonBox);
    setLayout(layout);
}


void StatusButtonBar::showMessage(const QString &message, int timeoutMSec)
{
    m_label->setText(message);
    if (timeoutMSec)
        QTimer::singleShot(timeoutMSec, m_label, SLOT(clear()));
}
