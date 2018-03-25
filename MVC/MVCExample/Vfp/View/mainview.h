#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}
namespace VirtualFrontPanel {

    class SetupTab;
    class MainView : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainView(QWidget *parent , VirtualFrontPanel::SetupTab &setup);
        ~MainView();

    private:
        Ui::MainView *ui;
        SetupTab& m_setupTab;
    };

}

#endif // MAINVIEW_H
