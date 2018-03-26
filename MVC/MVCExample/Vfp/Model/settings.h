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
        QString GetApplicationName() const {return m_applicationName;}
        QString GetApplicationShortName() const {return m_applicationShortName;}
        QString GetHostName() const {return m_hostName;}
        quint16 GetPortNumber() const {return m_portNumber;}
        int GetShortWaitMs() const {return m_shortWaitMs;}
        int GetLongWaitMs() const {return m_longWaitMs;}
        QStringListModel& getCommandsAsModel() const {return m_modelCommands;}


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
        int m_longWaitMs;
        int m_shortWaitMs;
        QStringListModel& m_modelCommands;


        JsonObjErrPair GetJsonObject(const QString &rawJson);
        void ShowJsonParsError(QJsonParseError jsonError);
        void SetupCommands(QJsonObject json_obj);
        QDir OpenConfigDirectory();
        void WriteDefaultsToStdConfig(QFile& stdConfigFile,const QString& settings);

        explicit Settings(const Settings& rhs) = delete;
        Settings& operator=(const Settings& rhs) = delete;


    };
}

#endif // SETTINGS_H


