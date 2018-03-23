#ifndef DATETIMEDELEGATE_H
#define DATETIMEDELEGATE_H

#include <QStyledItemDelegate>


class QModelIndex;
class QPainter;
class QStyleOptionViewItem;


class DateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DateTimeDelegate(QObject *parent=0)
        : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

private:
    QRectF clockRect(const QRectF &rect, const qreal &diameter) const;
    void drawClockFace(QPainter *painter, const QRectF &rect,
                       const QDateTime &lastModified) const;
    void drawClockHand(QPainter *painter, const QPointF &center,
            const qreal &length, const qreal &degrees) const;
    void drawDate(QPainter *painter,
            const QStyleOptionViewItem &option, const qreal &size,
            const QDateTime &lastModified) const;
};
#endif // DATETIMEDELEGATE_H
