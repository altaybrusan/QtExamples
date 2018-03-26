#include "settings.h"
#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <utility> // for including, std::pair
#include <QJsonArray>
#include <QStringListModel>
#include <QMessageBox>

namespace VirtualFrontPanel {

    static auto RESOURCE_PREFIX=QStringLiteral(":/json");

    Settings::Settings(QObject *parent, QString fileName):
        QObject(parent),
        m_fileName(fileName),
        m_modelCommands(*new QStringListModel(this))
    {
       // ReadJsonFile();

    }

    QString Settings::ReadJsonFile()
    {
        auto default_settings= ReadJsonFromInternalResources(); // if there is no user settings
        return default_settings;
    }

    void Settings::SendErrorMessage(const QString &msg)
    {
        emit NotifyStatusMessage(msg);
    }

    QString Settings::ReadJsonFromInternalResources()
    {
        QDir res_dir(RESOURCE_PREFIX);
        if(!res_dir.exists())
        {

            SendErrorMessage("Internal resource path missing " + res_dir.canonicalPath());
            return "";
        }

        auto path = res_dir.filePath(m_fileName);
        QFile res_file(path);
        if(!res_file.open(QFile::ReadOnly|QFile::Text))
        {
            SendErrorMessage("Could not open internal resource " + path);
            return "";
        }

        QString settings= res_file.readAll();
        return settings; // json -> QString

    }

    void Settings::ParsJsonData()
    {
        QString raw_json =ReadJsonFile();
        if(raw_json.size() == 0) return; // check if settings are empty?

        auto json_result = GetJsonObject(raw_json);
        auto json_err = json_result.second;
        if(json_err.error != QJsonParseError::NoError)
        {
            // Show error
            ShowJsonParsError(json_err);
        }
        auto json_obj = json_result.first;
        m_applicationName=json_obj["applicationTitle"].toString();
        m_applicationShortName=json_obj["appShortName"].toString();
        m_hostName=json_obj["hostname"].toString();
        m_portNumber=json_obj["port"].toInt();
        m_waitMs=json_obj["tcpLongWaitMs"].toInt();
        m_readWaitMs=json_obj["tcpShortWaitMs"].toInt();
        SetupCommands(json_obj);

    }

    // Row_Json<<QString>> ---> JSonDocument ---> JsonObject
    //                     ---> JSonError
    // < JsonObject, JSonError > ---> RETURNED

    JsonObjErrPair Settings::GetJsonObject(const QString& rawJson)
    {

        QJsonParseError json_pars_error;
        QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(),
                                                         &json_pars_error);
        QJsonObject json_obj= json_doc.object();
        return std::make_pair(json_obj,json_pars_error);


    }

    void Settings::ShowJsonParsError(QJsonParseError jsonError)
    {
        QString msg= tr("Error parsing Json settingsfile. \n");
        msg.append(jsonError.errorString());
        QMessageBox::critical(0,tr("Virtual Front Panel (VFP)"),msg);


    }

    void Settings::SetupCommands(QJsonObject json_obj)
    {
        QJsonArray cmd_array = json_obj["commands"].toArray();
        QStringList cmd_list;
        for(auto item:cmd_array)
        {
            cmd_list.append(item.toString());
        }
        m_modelCommands.setStringList(cmd_list);
    }

}
