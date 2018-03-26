#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QObject>

namespace VirtualFrontPanel {

    class InstSocket;

    class Instrument : public QObject
    {
        Q_OBJECT
    public:
        explicit Instrument(QObject *parent ,InstSocket& socket);
        virtual ~Instrument();
        void Connect();
        void Disconnect();
        bool IsConnected() const;
        QString GetHostName() const;
        quint16 GetPort() const;
        void SetLongWaitMs(int value);
        void SetShortWaitMs(int value);

    signals:
        void NotifyConnected();
        void NotifyDisconnected();
        void NotifyDataSent(const QString& datasent);
        void NotifyDataReceived(const QString& readData);
        void NotifyErrorDetected(const QString& errorMsg);
        void NotifyStatusUpdated(const QString& statusMsg);

    public slots:
        void onHostNameChanged(const QString& hostName);
        void onPortNameChanged(quint16 port);
        void onConnected();
        void onDisconnected();
        void onSendRequest(const QString& dataToSend);
        void onReceiveRequest();


    private:
        InstSocket& m_instSocket;
        QString m_lastCommandSent;

        void WireConnections();
    };

}

#endif // INSTRUMENT_H
