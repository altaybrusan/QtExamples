#ifndef STANDARDTABLEMODEL_H
#define STANDARDTABLEMODEL_H
#include <QStandardItemModel>

class StandardTableModel: public QStandardItemModel
{
    Q_OBJECT

public:
    explicit StandardTableModel(QObject *parent=0);

    QString filename() const { return m_filename; }
    void clear();
    void load(const QString &filename=QString());
    void save(const QString &filename=QString());

private:
    void initialize();

    QString m_filename;
};

#endif // STANDARDTABLEMODEL_H
