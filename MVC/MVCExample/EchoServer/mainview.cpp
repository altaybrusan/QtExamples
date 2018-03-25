#include "mainview.h"
#include "ui_mainview.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

static int PORT_NUMBER= 23;
static int WAIT_FOR_DATA_MS = 200;
MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    m_server(new QTcpServer(this)),
    m_socket(nullptr), //nullptr is defined in c++11 add it via: QMAKE_CXXFLAGS += -std=c++11
    ui(new Ui::MainView)
{

    ui->setupUi(this);
    ui->stopServerBtn->setEnabled(false);
    connect(m_server,&QTcpServer::newConnection,this,&MainView::ExchangeData);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::on_startServerBtn_clicked()
{
    if(StartServer())
    {
        ui->stopServerBtn->setEnabled(true);
        ui->startServerBtn->setEnabled(false);
    }
}

void MainView::on_stopServerBtn_clicked()
{
    StopServer();
    ui->stopServerBtn->setEnabled(false);
    ui->startServerBtn->setEnabled(true);
}

bool MainView::StartServer()
{

    bool result = m_server->listen(QHostAddress::Any,PORT_NUMBER);

    if(!result)
    {
        QMessageBox::critical(this,tr("Echo Server"),
                              tr("unable to start server: %1")
                              .arg(m_server->errorString()));
        return false;
    }

    return true;


}

void MainView::StopServer()
{
    m_server->close();
    if((m_socket != nullptr) && m_socket->isOpen())
    {
        m_socket->close();
    }

}

void MainView::ExchangeData()
{
    // Give me the next pending socket.
    // this is not a good practice.
    m_socket = m_server->nextPendingConnection();
    if(m_socket->isOpen())
    {
        connect(m_socket,&QTcpSocket::readyRead,this,&MainView::EchoReadData);
    }

}

void MainView::EchoReadData()
{
    m_socket->write("<echoserver>\n");
    QString result;
    while(!m_socket->atEnd())
    {
        result.append(m_socket->readAll());
        m_socket->waitForReadyRead(WAIT_FOR_DATA_MS);
    }
    m_socket->write(qPrintable(result));
    m_socket->write("\n</echoserver>\n");

}
