#include <QApplication>
#include "startup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    VirtualFrontPanel::MainView w;
//    w.show();
    VirtualFrontPanel::Startup startup;
    startup.Show();


    return a.exec();
}
