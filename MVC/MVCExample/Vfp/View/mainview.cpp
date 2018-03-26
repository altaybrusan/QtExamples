#include "mainview.h"
#include "ui_mainview.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "View/aboutbox.h"

namespace VirtualFrontPanel {

    MainView::MainView(QWidget *parent,SetupTab &setup,ControlTab& controlTab) :
        m_setupTab(setup),
        QMainWindow(parent),
        ui(new Ui::MainView)
    {
        ui->setupUi(this);
        m_setupTab.setParent(this);
        controlTab.setParent(this);
        ui->setupTabLayout->addWidget(&m_setupTab);
        ui->controlTabLayout->addWidget(&controlTab);

    }
    MainView::~MainView()
    {
        delete ui;
    }
}




void VirtualFrontPanel::MainView::on_action_Exit_triggered()
{
    QApplication::quit();// take a look at main.cpp too
}

void VirtualFrontPanel::MainView::on_action_About_triggered()
{
    AboutBox about_box;
    about_box.show();
    about_box.exec();

}
