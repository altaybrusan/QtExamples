#include "controltab.h"
#include "ui_controltab.h"
#include "utils.h"
namespace VirtualFrontPanel {
    ControlTab::ControlTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ControlTab)
    {
        ui->setupUi(this);
    }

    ControlTab::~ControlTab()
    {
        Utils::DestructorMsg(this);
        delete ui;
    }

    void ControlTab::EnablePanel(bool isEnabled)
    {
        ui->controlTabPanel->setEnabled(isEnabled);
    }
    void ControlTab::on_pulsSpinBox_valueChanged(double value)
    {
        emit NotifyPulsWidthChanged(value);
    }
}



