#ifndef STATUSBUTTONBAR_H
#define STATUSBUTTONBAR_H

#include <QLabel>
#include <QWidget>

class QCheckBox;
class QDialogButtonBox;

class StatusButtonBar : public QWidget
{
    Q_OBJECT
public:

    explicit StatusButtonBar(QWidget *parent=0);

    QLabel *label() { return m_label; }
    QCheckBox *checkBox() { return m_checkBox; }
    QDialogButtonBox *buttonBox() { return m_buttonBox; }


public slots:
    void showMessage(const QString &message, int timeoutMSec=0);
    void clear() { m_label->clear(); }

private:
    QLabel *m_label;
    QCheckBox *m_checkBox;
    QDialogButtonBox *m_buttonBox;
};

#endif // STATUSBUTTONBAR_H
