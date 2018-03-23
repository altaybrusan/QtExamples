#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QComboBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QRadioButton;
class QSpinBox;
class QTableView;
#ifdef CUSTOM_MODEL
class TableModel;
#else
class StandardTableModel;
#endif
#include "proxymodel.h"
#include "uniqueproxymodel.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void load();
    void load(const QString &filename);
    void setDirty() { setWindowModified(true); }
    void radioButtonClicked();
    void updateUi();
    bool save();
    void addZipcode();
    void deleteZipcode();

private:
    Ui::MainWindow *ui;
    void createWidgets();
    void createComboBoxModels();
    void createComboBoxModel(QComboBox *comboBox, int column);
    void createConnections();
    bool okToClearData();
    bool okToDelete(QWidget *parent,
                    const QString &title,
                    const QString &text,
                    const QString &detailedText=QString());
    void enableButtons(bool enable=true);
    bool matchingColumn(const QString &value, int row, int column);
    void restoreFilters();
    void reportFilterEffect();

    void performSelection();


#ifdef CUSTOM_MODEL
    TableModel *model;
#else
    StandardTableModel *model;
#endif
    ProxyModel *proxyModel;
    bool loading;
};

#endif // MAINWINDOW_H
