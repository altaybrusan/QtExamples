#include "provider.h"
#include "Model/settings.h"
#include "QString"
#include "utils.h"
namespace VirtualFrontPanel {

    static QString SETTING_FILE= QStringLiteral("settings.json");
    std::unique_ptr<Settings> Provider::m_instanceSettings =nullptr;

    Settings &Provider::GetSettingsAsSingleton()
    {
        if(m_instanceSettings ==nullptr)
        {
            m_instanceSettings = Utils::make_unique<Settings>(nullptr,SETTING_FILE);
        }

        return *m_instanceSettings;
    }
}

