#ifndef SETUPVIEWMGR_H
#define SETUPVIEWMGR_H

#include <QObject>
namespace VirtualFrontPanel {

    class SetupTab;
    class Instrument;
    class Settings;

    // enabling/disabling part of view is the job of this class!
    class SetupViewManager : public QObject
    {
        Q_OBJECT
    public:
        explicit SetupViewManager(QObject *parent ,
                              SetupTab &tab,
                              Instrument &inst,
                              Settings &config);
        ~SetupViewManager();

    signals:
        void NotifyStatusUpdated(const QString& value);
        void NotifyConnectEnabled(bool value);
        void NotifyDisconnectEnabled(bool value);
        void NotifyDirectCommandsEnabled(bool value);
        void NotifyControlTabEnabled(bool value);

    private slots:
        void onConnected();
        void onDisconnected();


    private:
        SetupTab& m_setupTab;
        Instrument& m_instrument;

        void WireSettings(Settings& config);
        void WireHostAndPort();
        void WireMessages();
        void WireButtons();
        void WireDisplayUpdate();
    };
}


#endif // SETUPVIEWMGR_H
