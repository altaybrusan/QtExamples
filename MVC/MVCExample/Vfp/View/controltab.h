#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QWidget>

namespace Ui {
    class ControlTab;
}

namespace VirtualFrontPanel {

    class ControlTab : public QWidget
    {
        Q_OBJECT

    public:
        explicit ControlTab(QWidget *parent = 0);
        ~ControlTab();
        void EnablePanel(bool isEnabled);

    signals:
        void NotifyPulsWidthChanged(double value);
    private slots:
        void on_pulsSpinBox_valueChanged(double value);

    private:
        Ui::ControlTab *ui;
    };

}

#endif // CONTROLTAB_H
