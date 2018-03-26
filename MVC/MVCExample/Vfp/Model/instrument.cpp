#include "instrument.h"
#include "Model/instsocket.h"
#include "utils.h"
#include <QDebug>

namespace VirtualFrontPanel {
    Instrument::Instrument(QObject *parent, InstSocket& socket) :
        QObject(parent),
        m_instSocket(socket),
        m_lastCommandSent("")
    {
        WireConnections();
    }

    Instrument::~Instrument()
    {
        Utils::DestructorMsg(this);
    }

    void Instrument::Connect()
    {
        Disconnect();
        bool connected= m_instSocket.Connect();
        if(!connected)
        {
            emit NotifyErrorDetected(tr("Error: Did not connected to the instrument"));
        }
    }
    bool Instrument::IsConnected() const
    {
        return m_instSocket.IsOpen();
    }

    QString Instrument::GetHostName() const
    {
        return m_instSocket.GetHostName();
    }

    quint16 Instrument::GetPort() const
    {
        return m_instSocket.GetPort();
    }
    void Instrument::onConnected()
    {
        emit NotifyConnected();
    }


    void Instrument::Disconnect()
    {
        if(m_instSocket.IsOpen())
        {
            m_instSocket.Disconnect();
        }
    }
    void Instrument::onDisconnected()
    {
        emit NotifyDisconnected();

    }

    void Instrument::onSendRequest(const QString &dataToSend)
    {
        m_lastCommandSent=dataToSend;
        qDebug()<<"Instrument ready to send data: "<<dataToSend;
        m_instSocket.WriteData(dataToSend);
        emit NotifyDataSent(dataToSend);
    }

    void Instrument::onReceiveRequest()
    {
        QString input_buffer = m_instSocket.ReadData();
        if(input_buffer.size()==0)
        {
            emit NotifyDataReceived("No data received.");
        }
        else
        {
            emit NotifyDataReceived(input_buffer);
        }
    }



    void Instrument::SetLongWaitMs(int value)
    {
        m_instSocket.SetLongWaitMs(value);
    }

    void Instrument::SetShortWaitMs(int value)
    {
        m_instSocket.SetShortWaitMs(value);
    }

    void Instrument::onHostNameChanged(const QString &hostName)
    {
        m_instSocket.SetHostName(hostName);
    }

    void Instrument::onPortChanged(quint16 port)
    {
        m_instSocket.SetPort(port);
    }


    void Instrument::WireConnections()
    {
        connect(&m_instSocket,&InstSocket::NotifyConnected,
                this,&Instrument::onConnected);
        connect(&m_instSocket,&InstSocket::NotifyDisconnected,
                this,&Instrument::onDisconnected);

    }

}
