#ifndef SETUPTAB_H
#define SETUPTAB_H

#include <QWidget>

namespace Ui {
class SetupTab;
}

class QStringListModel;
namespace VirtualFrontPanel {
    class SetupTab : public QWidget
    {
        Q_OBJECT

    public:
        explicit SetupTab(QWidget *parent = 0);
        ~SetupTab();

        void SetHostName(const QString& value);
        void SetPortName(quint16 value);
        void SetCommands(QStringListModel& commands);

    signals:
        void NotifyHostNameChanged(const QString& value);
        void NotifyPortChanged(quint16 value);
        void NotifyConnectClicked();
        void NotifyDisconnectClicked();
        void NotifySendClicked(const QString& dataToSend);
        void NotifyReceivedClicked();
    public slots:
        void onStatusUpdated(const QString& statusMsg);
        void onConnected();
        void onDisconnected();
        void onDataSent(const QString& dataSent);
        void onDataReceived(const QString& dataRead);
        void onConnectBtnEnabled(bool isEnabled);
        void onDisconnectBtnEnabled(bool isEnabled);
        void onDirectCommandsEnabled(bool isEnabled);
        void onControlTabEnabled(bool isEnabled);

    private slots:
        void on_ipAddressEditLine_editingFinished();
        void on_portEditLine_editingFinished();
        void on_connectBtn_clicked();
        void on_disconnectBtn_clicked();
        void on_sendBtn_clicked();
        void on_receiveBtn_clicked();
        void on_clearBtn_clicked();

    private:
        Ui::SetupTab *ui;
    };

}

#endif // SETUPTAB_H
