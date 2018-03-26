#ifndef STARTUP_H
#define STARTUP_H
#include <QWidget>
#include <QObject>
namespace VirtualFrontPanel {

    class MainView;
    class SetupTab;
    class Instrument;
    class SetupViewManager;

    class Startup final:public QObject
    {
        Q_OBJECT
    public:
        explicit Startup();
        void Show() const;

        ~Startup();

    private:
        SetupTab& m_setupTab;
        MainView& m_mainView;
        Instrument* m_instrument;
        SetupViewManager* m_setupViewMgr;

        explicit Startup(const Startup& rhs)=delete;
        Startup& operator=(const Startup& rhs)=delete;


    };
}

#endif // STARTUP_H


