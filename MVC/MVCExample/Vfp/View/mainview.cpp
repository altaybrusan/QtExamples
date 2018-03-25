#include "mainview.h"
#include "ui_mainview.h"
#include "View/setuptab.h"

namespace VirtualFrontPanel {

    MainView::MainView(QWidget *parent,VirtualFrontPanel::SetupTab &setup) :
        m_setupTab(setup),
        QMainWindow(parent),
        ui(new Ui::MainView)
    {
        ui->setupUi(this);
        m_setupTab.setParent(this);
        ui->setupTabLayout->addWidget(&m_setupTab);

    }
    MainView::~MainView()
    {
        delete ui;
    }
}



