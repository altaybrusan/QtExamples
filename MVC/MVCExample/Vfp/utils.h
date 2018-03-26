#ifndef UTILS_H
#define UTILS_H
#include <QWidget>
#include <memory>

namespace VirtualFrontPanel {

    class Utils
    {
    public:
        Utils();

        static void DestructorMsg(const QString& value);
        static void DestructorMsg(const QObject* const object);
        template<typename T,typename... Args>
        static std::unique_ptr<T> make_unique(Args&&... args)
        {
           return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
    private:
    };
}

#endif // UTILS_H


