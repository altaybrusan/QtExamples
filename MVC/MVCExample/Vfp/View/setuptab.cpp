#include "setuptab.h"
#include "ui_setuptab.h"
#include <QStringListModel>
#include "utils.h"
namespace VirtualFrontPanel {

    SetupTab::SetupTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SetupTab)
    {
        ui->setupUi(this);
    }

    SetupTab::~SetupTab()
    {
        Utils::DestructorMsg(this);
        delete ui;
    }

    void SetupTab::SetHostName(const QString &value)
    {
        ui->ipAddressEditLine->setText(value);
        emit NotifyHostNameChanged(value);
    }

    void SetupTab::SetPortName(quint16 value)
    {
        ui->portEditLine->setText(QString::number(value));
        emit NotifyPortChanged(value);
    }

    void SetupTab::SetCommands(QStringListModel &commands)
    {
        ui->commandsCBox->setModel(&commands);
    }

    void SetupTab::onStatusUpdated(const QString &statusMsg)
    {
        ui->instrumentMessagesTxtEditor->append(statusMsg);
    }

    void SetupTab::onConnected()
    {
        auto connect_msg = QString(tr("Connected."));
        ui->instrumentMessagesTxtEditor->append(connect_msg);
    }

    void SetupTab::onDisconnected()
    {
        auto disconnect_msg = QString(tr("Disconnected."));
        ui->instrumentMessagesTxtEditor->append(disconnect_msg);
    }

    void SetupTab::onDataSent(const QString &dataSent)
    {
        ui->instrumentMessagesTxtEditor->append("Data sent: "+ dataSent);
    }

    void SetupTab::onDataReceived(const QString &dataRead)
    {
        ui->instrumentMessagesTxtEditor->append("Data received: "+ dataRead);
    }

    void SetupTab::onConnectBtnEnabled(bool isEnabled)
    {
        ui->connectBtn->setEnabled(isEnabled);
    }

    void SetupTab::onDisconnectBtnEnabled(bool isEnabled)
    {
        ui->disconnectBtn->setEnabled(isEnabled);
    }

    void SetupTab::onDirectCommandsEnabled(bool isEnabled)
    {
        ui->directCommandsGBox->setEnabled(isEnabled);
    }

    void SetupTab::onControlTabEnabled(bool isEnabled)
    {
        //TODO
    }

    void SetupTab::on_ipAddressEditLine_editingFinished()
    {
        emit NotifyHostNameChanged(ui->ipAddressEditLine->text());

    }

    void SetupTab::on_portEditLine_editingFinished()
    {
        bool ok;
        int result= ui->portEditLine->text().toInt(&ok);
        if(!ok || (result > USHRT_MAX))
        {
            ui->instrumentMessagesTxtEditor->append(tr("invalid port number ")+ result);
        }
        else
        {
            emit NotifyPortChanged(result);
        }

    }

    void SetupTab::on_connectBtn_clicked()
    {
        emit NotifyConnectClicked();

    }

    void SetupTab::on_disconnectBtn_clicked()
    {
        emit NotifyDisconnectClicked();

    }

    void SetupTab::on_sendBtn_clicked()
    {
        emit NotifySendClicked(ui->commandsCBox->currentText());
    }

    void SetupTab::on_receiveBtn_clicked()
    {
        emit NotifyReceivedClicked();
    }

    void SetupTab::on_clearBtn_clicked()
    {
        ui->instrumentMessagesTxtEditor->clear();
    }



}// namespace end





