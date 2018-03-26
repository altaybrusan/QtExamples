#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;

namespace VirtualFrontPanel {

    typedef std::pair<QJsonObject,QJsonParseError> JsonObjErrPair;
    class Settings:public QObject
    {
        Q_OBJECT
    public:
        explicit Settings(QObject* parent,QString fileName);
        void ParsJsonData();

    signals:
        void NotifyStatusMessage(QString message);

    private:
        QString m_fileName;
        QString ReadJsonFile();
        void SendErrorMessage(const QString& msg);
        QString ReadJsonFromInternalResources();


        QString m_applicationName;
        QString m_applicationShortName;
        QString m_hostName;
        quint16 m_portNumber;
        int m_waitMs;
        int m_readWaitMs;
        QStringListModel& m_modelCommands;




        explicit Settings(const Settings& rhs)= delete;
        Settings& operator=(const Settings& rhs)= delete;
        JsonObjErrPair GetJsonObject(const QString &rawJson);
        void ShowJsonParsError(QJsonParseError jsonError);
        void SetupCommands(QJsonObject json_obj);
     };
}

#endif // SETTINGS_H


