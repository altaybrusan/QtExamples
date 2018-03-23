#ifndef ZIPCODESPINBOX_H
#define ZIPCODESPINBOX_H
#include "global.h"
#include <QSpinBox>


class ZipcodeSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit ZipcodeSpinBox(QWidget *parent)
        : QSpinBox(parent)
    {
        setRange(MinZipcode, MaxZipcode);
        setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    }

protected:
    QString textFromValue(int value) const
        { return QString("%1").arg(value, 5, 10, QChar('0')); }
};

#endif // ZIPCODESPINBOX_H
