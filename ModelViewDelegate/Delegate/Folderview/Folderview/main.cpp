#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(a.translate("main", "Folder View"));
#ifdef Q_WS_MAC
    app.setCursorFlashTime(0);
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
