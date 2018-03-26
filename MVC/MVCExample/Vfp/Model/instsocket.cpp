#include "instsocket.h"
#include <QTcpSocket>
#include <QDebug>
#include "utils.h"
namespace VirtualFrontPanel {

    InstSocket::InstSocket(QObject *parent) :
        QObject(parent),
        m_socket(*new QTcpSocket(this)),
        m_hostName(""),
        m_port(0),
        m_shortWaitTimeMs(0),
        m_longWaitTimeMs(0)
    {
        connect(&m_socket,&QTcpSocket::connected,
                this,&InstSocket::onConnected);
        connect(&m_socket,&QTcpSocket::disconnected,
                this,&InstSocket::onDisconnected);

    }

    bool InstSocket::Connect()
    {
        qDebug()<<"Attempting to connect to "<<m_hostName<<
                  "on port"<<m_port<<
                  "with wait time "<<m_longWaitTimeMs;
        m_socket.connectToHost(m_hostName,m_port,QTcpSocket::ReadWrite);
        return m_socket.waitForConnected(m_longWaitTimeMs);
    }

    bool InstSocket::IsOpen()
    {
        return m_socket.isOpen();
    }

    void InstSocket::Disconnect()
    {
        if(!m_socket.isOpen()) return;
        m_socket.disconnectFromHost();
    }

    void InstSocket::SetHostName(const QString &value)
    {
        m_hostName = value;
    }

    void InstSocket::SetPort(quint16 value)
    {
        m_port =value;
    }

    QString InstSocket::ReadData() const
    {
        if(!m_socket.isReadable())
        {
            return "Error: Socket is not readable";
        }
        QString result;
        // the device may send messages in part
        // assumption: computer is really fast.
        while(!m_socket.atEnd())
        {
            result.append(m_socket.readAll());
            // give this opportunity for slow device to send more.
            m_socket.waitForReadyRead(m_shortWaitTimeMs);
        }
        return result;
    }

    void InstSocket::WriteData(const QString &data) const
    {
        int bytes_written = m_socket.write(qPrintable(data));
        qDebug()<<  "Bytes written"<<bytes_written;
    }

    InstSocket::~InstSocket()
    {
        Utils::DestructorMsg(this);
    }

    void InstSocket::onConnected()
    {
        emit NotifyConnected();
    }

    void InstSocket::onDisconnected()
    {
        emit NotifyDisconnected();
    }

}

