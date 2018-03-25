#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "utils.h"
namespace VirtualFrontPanel {
    Startup::Startup() :
        QObject(nullptr),
        m_setupTab(*new SetupTab(nullptr)),
        m_mainView(*new MainView(nullptr,m_setupTab))
    {
    }
    void Startup::Show() const
    {
        m_mainView.show();
    }

    Startup::~Startup()
    {
        VirtualFrontPanel::Utils::DestructorMsg(this);
        delete& m_mainView; // the m_setup is parented by m_mainview,
                            // it is automatically deleted
    }
}
