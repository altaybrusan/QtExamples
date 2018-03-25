#ifndef SETUPTAB_H
#define SETUPTAB_H

#include <QWidget>

namespace Ui {
class SetupTab;
}

namespace VirtualFrontPanel {
    class SetupTab : public QWidget
    {
        Q_OBJECT

    public:
        explicit SetupTab(QWidget *parent = 0);
        ~SetupTab();

    private:
        Ui::SetupTab *ui;
    };

}

#endif // SETUPTAB_H
