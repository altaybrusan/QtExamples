#ifndef INSTSOCKET_H
#define INSTSOCKET_H

#include <QObject>

class QTcpSocket; // this is defined outside of namespace

namespace VirtualFrontPanel {
    class InstSocket : public QObject
    {
        Q_OBJECT
    public:
        explicit InstSocket(QObject *parent = nullptr);
        bool Connect();
        bool IsOpen();
        void Disconnect();

        QString GetHostName() const {return m_hostName;}
        void SetHostName(const QString& value);
        quint16 GetPort() const {return m_port;}
        void SetPort(quint16 value);
        void SetLongWaitMs(int value){m_longWaitTimeMs=value;}
        void SetShortWaitMs(int value){m_shortWaitTimeMs=value;}
        QString ReadData() const;
        void WriteData(const QString &data)const;
        ~InstSocket();

    signals:
        void NotifyConnected();
        void NotifyDisconnected();
    public slots:

    private slots:
        void onConnected();
        void onDisconnected();

    private:
        QTcpSocket& m_socket;
        QString m_hostName;
        quint16 m_port; //16-bits in all platforms
        int m_shortWaitTimeMs;
        int m_longWaitTimeMs;
        explicit InstSocket(const InstSocket& rhs) =delete;
        InstSocket& operator=(const InstSocket& rhs) =delete;
    };
}


#endif // INSTSOCKET_H
