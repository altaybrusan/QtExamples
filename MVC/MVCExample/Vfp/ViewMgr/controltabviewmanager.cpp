#include "controltabviewmanager.h"
#include  "Model/instrument.h"
#include "View/controltab.h"
#include "utils.h"

namespace VirtualFrontPanel {
    ControlTabViewManager::ControlTabViewManager(QObject *parent,
                                                 ControlTab &tab,
                                                 Instrument &inst) :
        QObject(parent),
        m_controlTab(tab),
        m_instrument(inst)
    {
        WireControls();
        WireConnected();
    }

    ControlTabViewManager::~ControlTabViewManager()
    {
        Utils::DestructorMsg(this);
    }

    void ControlTabViewManager::onConnected()
    {
        //anothe way to connect view to model (beside, signal and slot)
        m_controlTab.EnablePanel(true);
    }

    void ControlTabViewManager::onDisconnected()
    {
        //anothe way to connect view to model (beside, signal and slot)
        m_controlTab.EnablePanel(false);
    }

    void ControlTabViewManager::WireControls()
    {
        connect(&m_controlTab,&ControlTab::NotifyPulsWidthChanged,
                &m_instrument,&Instrument::onPulseWidthChanged);
    }

    void ControlTabViewManager::WireConnected()
    {
        connect(&m_instrument,&Instrument::NotifyConnected,
                this,&ControlTabViewManager::onConnected);
        connect(&m_instrument,&Instrument::NotifyDisconnected,
                this,&ControlTabViewManager::onDisconnected);
    }
}

