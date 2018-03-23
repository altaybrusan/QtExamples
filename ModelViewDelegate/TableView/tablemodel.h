#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "zipcodeitem.h"
#include <QAbstractTableModel>

class TableModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent=0)
        : QAbstractTableModel(parent) {}

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index,
                  int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role=Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role=Qt::EditRole);
    bool setHeaderData(int, Qt::Orientation, const QVariant&,
                       int=Qt::EditRole) { return false; }

    bool insertRows(int row, int count,
                    const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex &parent=QModelIndex());

    QString filename() const { return m_filename; }
    void load(const QString &filename=QString());
    void save(const QString &filename=QString());

private:
    QString m_filename;
    QList<ZipcodeItem> zipcodes;
};

#endif // TABLEMODEL_H
