#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QCloseEvent;
class QComboBox;
class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void convertOrCancel();
    void updateUi();
    void checkIfDone();
    void announceProgress(bool saved, const QString &message);
    void sourceTypeChanged(const QString &sourceType);

protected:
#ifdef USE_QTCONCURRENT
    bool event(QEvent *event);
#endif
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    void createWidgets();
    void createLayout();
    void createConnections();
    void convertFiles(const QStringList &sourceFiles);

    QLabel *directoryLabel;
    QLineEdit *directoryEdit;
    QLabel *sourceTypeLabel;
    QComboBox *sourceTypeComboBox;
    QLabel *targetTypeLabel;
    QComboBox *targetTypeComboBox;
    QPlainTextEdit *logEdit;
    QPushButton *convertOrCancelButton;
    QPushButton *quitButton;

    int total;
    int done;
    volatile bool stopped;

};

#endif // MAINWINDOW_H
