#ifndef PROVIDER_H
#define PROVIDER_H
#include <memory>

namespace VirtualFrontPanel {

    class Settings;
    class Provider
    {
    public:
        Provider();
        static Settings &GetSettingsAsSingleton();

    private:
        static std::unique_ptr<Settings> m_instanceSettings;

        explicit Provider(const Provider& rhs) = delete;
        Provider& operator=(const Provider& rhs) = delete;
    };
}


#endif // PROVIDER_H
