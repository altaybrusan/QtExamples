#ifndef STANDARDITEM_H
#define STANDARDITEM_H

#include <QDateTime>
#include <QList>
#include <QPair>
#include <QStandardItem>


class StandardItem : public QStandardItem
{
public:
    explicit StandardItem(const QString &text, bool done);

    QStandardItem *todayItem() const { return m_today; }
    QStandardItem *totalItem() const { return m_total; }
    void addDateTime(const QDateTime &start, const QDateTime &end)
        { m_dateTimes << qMakePair(start, end); }
    QList<QPair<QDateTime, QDateTime>> dateTimes() const
        { return m_dateTimes; }
    void incrementLastEndTime(int msec);

    QString todaysTime() const;
    QString totalTime() const;

private:
    int minutesForTask(bool onlyForToday) const;

    QStandardItem *m_today;
    QStandardItem *m_total;
    QList<QPair<QDateTime, QDateTime>> m_dateTimes;
};

#endif // STANDARDITEM_H
