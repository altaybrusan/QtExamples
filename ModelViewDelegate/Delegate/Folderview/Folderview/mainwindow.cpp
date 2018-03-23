#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include "datetimedelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    model(new QFileSystemModel),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    model->setRootPath(QDir::homePath());
    QModelIndex index = model->index(QDir::homePath());
    //    QHeaderView *header = viewWithoutDelegate->header();
    //    header->setResizeMode(QHeaderView::ResizeToContents);
    ui->viewWithoutDelegate->setModel(model);
    ui->viewWithoutDelegate->setColumnHidden(1, true); // for screenshots
    ui->viewWithoutDelegate->setColumnHidden(2, true); // for screenshots
    ui->viewWithoutDelegate->scrollTo(index);
    ui->viewWithoutDelegate->expand(index);
    ui->viewWithoutDelegate->setCurrentIndex(index);

    ui->view->setItemDelegateForColumn(3, new DateTimeDelegate);
    //    header = view->header();
    //    header->setResizeMode(QHeaderView::ResizeToContents);
    ui->view->setModel(model);
    ui->view->setColumnHidden(1, true);
    ui->view->setColumnHidden(2, true);
    ui->view->scrollTo(index);
    ui->view->expand(index);
    ui->view->setCurrentIndex(index);

    ui->statusBar->clearMessage(); // create statusbar + useful size grip
    this->resize(800, 480);
    this->setWindowTitle( QApplication::applicationName());



}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}
