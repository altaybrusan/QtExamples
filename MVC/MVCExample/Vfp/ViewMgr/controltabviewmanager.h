#ifndef CONTROLTABVIEWMANAGER_H
#define CONTROLTABVIEWMANAGER_H

#include <QObject>

namespace VirtualFrontPanel {

    class ControlTab;
    class Instrument;
    class ControlTabViewManager : public QObject
    {
        Q_OBJECT
    public:
        explicit ControlTabViewManager(QObject *parent , ControlTab& tab, Instrument& inst);
        ~ControlTabViewManager();
    signals:

    public slots:
        void onConnected();
        void onDisconnected();

    private:
        ControlTab& m_controlTab;
        Instrument& m_instrument;

        void WireControls();
        void WireConnected();
    };
}


#endif // CONTROLTABVIEWMANAGER_H
