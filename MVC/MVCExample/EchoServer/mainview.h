#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}

class QTcpServer;
class QTcpSocket;
class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void on_startServerBtn_clicked();

    void on_stopServerBtn_clicked();

private:
    Ui::MainView *ui;
    QTcpServer* m_server;
    QTcpSocket* m_socket;
    bool StartServer();
    void StopServer();
    void ExchangeData();
    void EchoReadData();
};

#endif // MAINVIEW_H
