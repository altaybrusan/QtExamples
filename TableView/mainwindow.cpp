#include "mainwindow.h"
#include "proxymodel.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "itemdelegate.h"
#include "uniqueproxymodel.h"
#include "tablemodel.h"
#include <QAbstractItemModel>
#if QT_VERSION >= 0x040600
#include <QScopedPointer>
#else
#include <QSharedPointer>
#endif
#include<QFileInfo>
#include<QFileDialog>
#include <exception>
#include <QDebug>
#include <QMessageBox>
#include "standardtablemodel.h"

const int StatusTimeout= 10000;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),loading(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef CUSTOM_MODEL
    model = new TableModel(this);
#else
    model = new StandardTableModel(this);
#endif
#ifdef MODEL_TEST
    (void) new ModelTest(model, this);
#endif

    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);

    createWidgets();
    createComboBoxModels();
    createConnections();

#ifdef CUSTOM_MODEL
    setWindowTitle(tr("%1 (Custom Model)[*]")
            .arg(QApplication::applicationName()));
#else
    setWindowTitle(tr("%1 (QStandardItemModel)[*]")
            .arg(QApplication::applicationName()));
#endif
    statusBar()->showMessage(tr("Ready"), StatusTimeout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    if (!okToClearData())
        return;
    QString filename(model->filename());
    QString dir(filename.isEmpty() ? QString(".")
                : QFileInfo(filename).canonicalPath());
    filename = QFileDialog::getOpenFileName(this,
            tr("%1 - Open").arg(QApplication::applicationName()),
            dir,
            tr("%1 (*.dat)").arg(QApplication::applicationName()));
    if (filename.isEmpty())
        return;

    enableButtons(false);
    QMetaObject::invokeMethod(this, "load", Qt::QueuedConnection,
                              Q_ARG(QString, filename));


}

void MainWindow::load(const QString &filename)
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    loading = true;
    try {
        model->load(filename);
        ui->tableView->resizeColumnsToContents();
        QHeaderView *header = ui->tableView->horizontalHeader();
        header->setSortIndicatorShown(true);
        header->setSortIndicator(0, Qt::AscendingOrder);
        createComboBoxModels();
        setWindowModified(false);
        setWindowTitle(tr("%1 - %2[*]")
                .arg(QApplication::applicationName())
                .arg(QFileInfo(filename).fileName()));
        statusBar()->showMessage(tr("Loaded %n zipcode(s) from %1",
                "", model->rowCount()).arg(filename), StatusTimeout);
    } catch (std::exception &error) {
        qDebug()<<tr("ErrorFailed to load %1: %2")
                .arg(filename).arg(QString::fromUtf8(error.what()));
    }
    loading = false;
    ui->tableView->setFocus();
    radioButtonClicked();
    enableButtons();
    QApplication::restoreOverrideCursor();
}



void MainWindow::radioButtonClicked()
{
    if (ui->dontFilterOrSelectRadioButton->isChecked()) {
        proxyModel->clearFilters();
        QItemSelectionModel *selectionModel =
                ui->tableView->selectionModel();
        selectionModel->clearSelection();
    }
    else
        updateUi();
}

void MainWindow::updateUi()
{
    if (loading || ui->dontFilterOrSelectRadioButton->isChecked())
        return;
    if (ui->filterRadioButton->isChecked())
        restoreFilters();
    else
        performSelection();

}


bool MainWindow::save()
{
    try {
        model->save();
        setWindowModified(false);
        setWindowTitle(tr("%1 - %2[*]")
                .arg(QApplication::applicationName())
                .arg(QFileInfo(model->filename()).fileName()));
        statusBar()->showMessage(tr("Saved %1")
                .arg(model->filename()), StatusTimeout);
        return true;
    } catch (std::exception &error) {
//        AQP::warning(this, tr("Error"), tr("Failed to save %1: %2")
//                .arg(model->filename())
//                .arg(QString::fromUtf8(error.what())));
        qDebug()<< tr("Error: Failed to save %1: %2").arg(model->filename()).arg(QString::fromUtf8(error.what()));
        return false;
    }

}

void MainWindow::createWidgets()
{
    ui->minimumZipSpinBox->setRange(MinZipcode, MaxZipcode);
    ui->minimumZipSpinBox->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->maximumZipSpinBox->setRange(MinZipcode, MaxZipcode);
    ui->maximumZipSpinBox->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->maximumZipSpinBox->setValue(MaxZipcode);


    ui->tableView->setModel(proxyModel);
    ui->tableView->setItemDelegate(new ItemDelegate(this));
    ui->tableView->verticalHeader()->setDefaultAlignment(
            Qt::AlignVCenter|Qt::AlignRight);

}

void MainWindow::createComboBoxModels()
{
    createComboBoxModel(ui->countyComboBox, County);
    createComboBoxModel(ui->stateComboBox, State);
}

void MainWindow::createComboBoxModel(QComboBox *comboBox, int column)
{
    delete comboBox->model();
    UniqueProxyModel *uniqueProxyModel = new UniqueProxyModel(column,this);
    uniqueProxyModel->setSourceModel(model);
    uniqueProxyModel->sort(column, Qt::AscendingOrder);
    comboBox->setModel(uniqueProxyModel);
    comboBox->setModelColumn(column);
}

void MainWindow::createConnections()
{
#ifdef CUSTOM_MODEL
    connect(model,
        SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
        this, SLOT(setDirty()));
#else
    connect(model, SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(setDirty()));
#endif
    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)),
            this, SLOT(setDirty()));
    connect(model, SIGNAL(modelReset()), this, SLOT(setDirty()));

    connect(ui->countyGroupBox, SIGNAL(toggled(bool)),
            this, SLOT(updateUi()));
    connect(ui->countyComboBox,
            SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(updateUi()));
    connect(ui->stateGroupBox, SIGNAL(toggled(bool)),
            this, SLOT(updateUi()));
    connect(ui->stateComboBox,
            SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(updateUi()));
    connect(ui->minimumZipSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(updateUi()));
    connect(ui->maximumZipSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(updateUi()));

    foreach (QRadioButton *radioButton, QList<QRadioButton*>()
             << ui->dontFilterOrSelectRadioButton << ui->filterRadioButton
             << ui->selectByCriteriaRadioButton)
        connect(radioButton, SIGNAL(clicked()),
                this, SLOT(radioButtonClicked()));

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(selectionChanged()));
    connect(ui->tableView->selectionModel(),
            SIGNAL(currentChanged(const QModelIndex&,
                                  const QModelIndex&)),
            this, SLOT(selectionChanged()));

    connect(ui->tableView->horizontalHeader(),
            SIGNAL(sectionClicked(int)),
            ui->tableView, SLOT(sortByColumn(int)));

    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(load()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addZipcode()));
    connect(ui->deleteButton, SIGNAL(clicked()),
            this, SLOT(deleteZipcode()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

}

bool MainWindow::okToClearData()
{
    if(isWindowModified())
    {
        //Q_ASSERT( &MainWindow::save && parent);
    #if QT_VERSION >= 0x040600
        QScopedPointer<QMessageBox> messageBox(new QMessageBox(this));
    #else
        QSharedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    #endif
        messageBox->setWindowModality(Qt::WindowModal);
        messageBox->setIcon(QMessageBox::Question);
        messageBox->setWindowTitle(QString("%1 - %2")
                .arg(QApplication::applicationName()).arg("Unsaved changes"));
        messageBox->setText("Save unsaved changes?");

//        if (!detailedText.isEmpty())
//            messageBox->setInformativeText("detailedText");
        messageBox->addButton(QMessageBox::Save);
        messageBox->addButton(QMessageBox::Discard);
        messageBox->addButton(QMessageBox::Cancel);
        messageBox->setDefaultButton(QMessageBox::Save);
        messageBox->exec();
        if (messageBox->clickedButton() ==
            messageBox->button(QMessageBox::Cancel))
            return false;
        if (messageBox->clickedButton() ==
            messageBox->button(QMessageBox::Save))
            return save();
    }
    return true;
}

bool MainWindow::okToDelete(QWidget *parent, const QString &title,
                            const QString &text, const QString &detailedText)
{
#if QT_VERSION >= 0x040600
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
#else
    QSharedPointer<QMessageBox> messageBox(new QMessageBox(parent));
#endif
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    QAbstractButton *deleteButton = messageBox->addButton(
            QObject::tr("&Delete"), QMessageBox::AcceptRole);
    messageBox->addButton(QObject::tr("Do &Not Delete"),
                          QMessageBox::RejectRole);
    messageBox->setDefaultButton(
            qobject_cast<QPushButton*>(deleteButton));
    messageBox->exec();
    return messageBox->clickedButton() == deleteButton;
}

void MainWindow::enableButtons(bool enable)
{
    foreach(QPushButton *button, QList<QPushButton*>() << ui->loadButton
            << ui->saveButton << ui->addButton << ui->deleteButton) {
        button->setEnabled(enable);
        button->repaint(); // update isn't "strong" enough on non-Mac
    }
}

bool MainWindow::matchingColumn(const QString &value, int row, int column)
{
    if (value.isEmpty())
        return true;
    QModelIndex index = proxyModel->index(row, column);
    return value == proxyModel->data(index).toString();
}

void MainWindow::restoreFilters()
{
    proxyModel->setMinimumZipcode(ui->minimumZipSpinBox->value());
    proxyModel->setMaximumZipcode(ui->maximumZipSpinBox->value());
    proxyModel->setCounty(ui->countyGroupBox->isChecked()
            ? ui->countyComboBox->currentText() : QString());
    proxyModel->setState(ui->stateGroupBox->isChecked()
            ? ui->stateComboBox->currentText() : QString());
    reportFilterEffect();
}

void MainWindow::reportFilterEffect()
{
    if (loading)
        return;
    statusBar()->showMessage(tr("Filtered %L1 out of %Ln zipcode(s)",
            "", model->rowCount()).arg(proxyModel->rowCount()),
                             StatusTimeout);
}

void MainWindow::addZipcode()
{
    ui->dontFilterOrSelectRadioButton->click();
#ifdef CUSTOM_MODEL
    if (!model->insertRow(model->rowCount()))
        return;
#else
    QList<QStandardItem*> items;
    QStandardItem *zipItem = new QStandardItem;
    zipItem->setData(MinZipcode, Qt::EditRole);
    items << zipItem;
    for (int i = 0; i < model->columnCount() - 1; ++i)
        items << new QStandardItem(tr("(Unknown)"));
    model->appendRow(items);
#endif
    ui->tableView->scrollToBottom();
    ui->tableView->setFocus();
    QModelIndex index = proxyModel->index(proxyModel->rowCount() - 1,
                                          Zipcode);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);

}

void MainWindow::deleteZipcode()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    if (!selectionModel->hasSelection())
        return;
    QModelIndex index = proxyModel->mapToSource(
            selectionModel->currentIndex());
    if (!index.isValid())
        return;
    int zipcode = model->data(model->index(index.row(),
                              Zipcode)).toInt();
    if (!okToDelete(this, tr("Delete Zipcode"),tr("Delete Zipcode %1?").arg(zipcode, 5, 10, QChar('0'))))
        return;
    bool filtered = ui->filterRadioButton->isChecked();
    bool selected = ui->selectByCriteriaRadioButton->isChecked();
    QString county = ui->countyGroupBox->isChecked()
            ? ui->countyComboBox->currentText() : QString();
    QString state = ui->stateGroupBox->isChecked()
            ? ui->stateComboBox->currentText() : QString();
    ui->dontFilterOrSelectRadioButton->click();

    model->removeRow(index.row(), index.parent());

    createComboBoxModels();
    if (!county.isEmpty())
        ui->countyComboBox->setCurrentIndex(
                ui->countyComboBox->findText(county));
    if (!state.isEmpty())
        ui->stateComboBox->setCurrentIndex(
                ui->stateComboBox->findText(state));
    if (filtered)
        ui->filterRadioButton->click();
    else if (selected)
        ui->selectByCriteriaRadioButton->click();

}

void MainWindow::performSelection()
{
    proxyModel->clearFilters();
    int minimumZipcode = ui->minimumZipSpinBox->value();
    int maximumZipcode = ui->maximumZipSpinBox->value();
    QString county = ui->countyGroupBox->isChecked()
            ? ui->countyComboBox->currentText() : QString();
    QString state = ui->stateGroupBox->isChecked()
            ? ui->stateComboBox->currentText() : QString();

    QItemSelection selection;
    int firstSelectedRow = -1;
    for (int row = 0; row < proxyModel->rowCount(); ++row) {
        QModelIndex index = proxyModel->index(row, Zipcode);
        int zipcode = proxyModel->data(index).toInt();
        if (zipcode < minimumZipcode || zipcode > maximumZipcode)
            continue;
        if (!matchingColumn(county, row, County))
            continue;
        if (!matchingColumn(state, row, State))
            continue;
        if (firstSelectedRow == -1)
            firstSelectedRow = row;
        QItemSelection rowSelection(index, index);
        selection.merge(rowSelection, QItemSelectionModel::Select);
    }
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    selectionModel->clearSelection();
    selectionModel->select(selection, QItemSelectionModel::Rows|
                                      QItemSelectionModel::Select);
    if (firstSelectedRow != -1)
        ui->tableView->scrollTo(proxyModel->index(firstSelectedRow, 0));
    statusBar()->showMessage(tr("Selected %L1 out of %Ln zipcode(s)",
            "", model->rowCount()).arg(selection.count()),
            StatusTimeout);
}
