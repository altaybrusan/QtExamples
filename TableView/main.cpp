#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QtWidgets> // added for Qt5

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setApplicationName(a.translate("main", "Zipcodes"));
//#ifdef Q_WS_MAC
//    app.setCursorFlashTime(0);
//#endif

//    QTranslator translator;
//    translator.load(AQP::applicationPathOf() + "/zipcodes_en.qm");
//    app.installTranslator(&translator);


    MainWindow w;
    w.resize(800, 640);
    w.show();

    return a.exec();
}
