#include "convertimagetask.h"
#include <QDir>
#include <QFileInfo>
#include <QImage>


void ConvertImageTask::run()
{
    foreach (const QString &source, m_sourceFiles) {
        if (*m_stopped)
            return;
        QImage image(source);
        QString target(source);
        target.chop(QFileInfo(source).suffix().length());
        target += m_targetType;
        if (*m_stopped)
            return;
        bool saved = image.save(target);

        QString message = saved
                ? QObject::tr("Saved '%1'")
                              .arg(QDir::toNativeSeparators(target))
                : QObject::tr("Failed to convert '%1'")
                              .arg(QDir::toNativeSeparators(source));
        QMetaObject::invokeMethod(m_receiver, "announceProgress",
                Qt::QueuedConnection, Q_ARG(bool, saved),
                Q_ARG(QString, message));
    }
}
