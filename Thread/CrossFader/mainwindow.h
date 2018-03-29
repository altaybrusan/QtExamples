#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QList>
#include <QMap>
#include <QMainWindow>
#include <QPointer>
#include <QProgressBar>


class CrossFader;
class StatusButtonBar;
class QLineEdit;
class QPushButton;
class QScrollArea;
class QSpinBox;


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
    void setFirstImage();
    void setLastImage();
    void generateOrCancelImages();
    void saving(const QString &filename);
    void saved(bool saved, const QString &filename);
    void finished();
    void updateUi();
    void quit();

private:
    Ui::MainWindow *ui;


    enum StopState {Stopping, Terminating};

    void createWidgets();
    void createLayout();
    void createConnections();
    void setImageFile(QLabel *targetLabel, const QString &which);
    void createAndRunACrossFader(int number, const QImage &firstImage, const QImage &lastImage);
    void cleanUp(StopState stopState=Stopping);


    QPushButton *firstButton;
    QLabel *firstLabel;
    QLabel *lastLabel;
    QLabel *baseNameLabel;
    QLineEdit *baseNameEdit;
    QLabel *numberLabel;
    QSpinBox *numberSpinBox;
    QPushButton *lastButton;
    QPushButton *generateOrCancelButton;
    QPushButton *quitButton;
    StatusButtonBar *statusBar;
    QScrollArea *scrollArea;
    QWidget *progressWidget;

    QMap<QString, QPointer<QProgressBar>> progressBarForFilename;// <---
    QList<QPointer<QLabel> > progressLabels;
    QList<QPointer<CrossFader> > crossFaders;
    bool canceled;
};

#endif // MAINWINDOW_H
