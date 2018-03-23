#ifndef THREADSAFEERRORINFO_H
#define THREADSAFEERRORINFO_H

#include <QMutex>
#include <QMutexLocker>
#include <QSet>


class ThreadSafeErrorInfo
{
public:
    explicit ThreadSafeErrorInfo() : m_count(0) {}

    int count() const
    {
        QMutexLocker locker(&mutex);
        return m_count;
    }


    QStringList errors() const
    {
        QMutexLocker locker(&mutex);
        return QStringList::fromSet(m_errors);
    }

    bool isEmpty() const
    {
        QMutexLocker locker(&mutex);
        return m_count == 0;
    }


    void add(const QString &error)
    {
        QMutexLocker locker(&mutex);
        ++m_count;
        m_errors << error;
    }

    void clear()
    {
        QMutexLocker locker(&mutex);
        m_count = 0;
        m_errors.clear();
    }

private:
    mutable QMutex mutex;
    int m_count;
    QSet<QString> m_errors;
};

#endif // THREADSAFEERRORINFO_H
