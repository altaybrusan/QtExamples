#ifndef STARTUP_H
#define STARTUP_H
#include <QWidget>
#include <QObject>
namespace VirtualFrontPanel {

    class MainView;
    class SetupTab;

    class Startup final:public QObject
    {
        Q_OBJECT
    public:
        explicit Startup();
        void Show() const;

        ~Startup();

    private:
        explicit Startup(const Startup& rhs)=delete;
        Startup& operator=(const Startup& rhs)=delete;

        SetupTab& m_setupTab;
        MainView& m_mainView;
    };
}

#endif // STARTUP_H


