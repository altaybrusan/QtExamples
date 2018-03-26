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
        void Disconnect() const;
        bool IsConnected() const;
        QString GetHostName() const;
        quint16 GetPort() const;
        void SetLongWaitMs(int value);
        void SetShortWaitMs(int value);

    signals:
        void NotifyConnected() const;
        void NotifyDisconnected() const;
        void NotifyDataSent(const QString& datasent) const;
        void NotifyDataReceived(const QString& readData) const;
        void NotifyErrorDetected(const QString& errorMsg) const;
        void NotifyStatusUpdated(const QString& statusMsg) const;

    public slots:
        void onHostNameChanged(const QString& hostName);
        void onPortChanged(quint16 port);
        void onConnected();
        void onDisconnected();
        void onSendRequest(const QString& dataToSend);
        void onReceiveRequest();
        void onPulseWidthChanged(double value);


    private:
        InstSocket& m_instSocket;
        QString m_lastCommandSent;

        void WireConnections();
    };

}

#endif // INSTRUMENT_H
