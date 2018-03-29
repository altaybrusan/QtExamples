#ifndef CROSSFADER_H
#define CROSSFADER_H

#include <QImage>
#include <QThread>

class CrossFader : public QThread
{
    Q_OBJECT

public:
    explicit CrossFader(const QString &filename, const QImage &first,
               const double &firstWeight, const QImage &last,
               const double &lastWeight, QObject *parent=0);

public slots:
    void stop() { m_stopped = true; }

signals:
    void progress(int);
    void saving(const QString&);
    void saved(bool, const QString&);

private:
    void run();

    const QString m_filename;
    QImage m_first;
    QImage m_last;
    const double m_firstWeight;
    const double m_lastWeight;
    volatile bool m_stopped;
};

#endif // CROSSFADER_H
