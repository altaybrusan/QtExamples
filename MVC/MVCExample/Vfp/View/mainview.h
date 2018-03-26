#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}
namespace VirtualFrontPanel {

    class SetupTab;
    class ControlTab;
    class MainView : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainView(QWidget *parent , SetupTab& setup,ControlTab& controlTab);
        ~MainView();

    private slots:
        void on_action_Exit_triggered();

        void on_action_About_triggered();

    private:
        Ui::MainView *ui;
        SetupTab& m_setupTab;
    };

}

#endif // MAINVIEW_H
