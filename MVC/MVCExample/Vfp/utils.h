#ifndef UTILS_H
#define UTILS_H
#include <QWidget>

namespace VirtualFrontPanel {

    class Utils
    {
    public:
        Utils();

        static void DestructorMsg(const QString& value);
        static void DestructorMsg(const QObject* const object);
    private:
    };
}

#endif // UTILS_H


