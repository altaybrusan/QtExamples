#include <QApplication>
#include "startup.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    VirtualFrontPanel::MainView w;
//    w.show();
    QObject::connect(&a,&QApplication::lastWindowClosed,
                     &a,&QApplication::quit);
    VirtualFrontPanel::Startup startup;
    startup.Show();


    return a.exec();
}
