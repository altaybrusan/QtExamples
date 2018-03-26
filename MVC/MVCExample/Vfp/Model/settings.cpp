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
#include <QStandardPaths>
#include <QDebug>

namespace VirtualFrontPanel {

    static const int PW_CMD_INDEX =5;
    static auto RESOURCE_PREFIX=QStringLiteral(":/json");

    Settings::Settings(QObject *parent, QString fileName):
        QObject(parent),
        m_fileName(fileName),
        m_modelCommands(*new QStringListModel(this))
    {
       // ReadJsonFile();

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
        m_longWaitMs=json_obj["tcpLongWaitMs"].toInt();
        m_shortWaitMs=json_obj["tcpShortWaitMs"].toInt();
        SetupCommands(json_obj);

    }

    QString Settings::ReadJsonFile()
    {
        auto default_settings= ReadJsonFromInternalResources(); // if there is no user settings
        QDir config_dir = OpenConfigDirectory();
        auto path = config_dir.filePath(m_fileName);
        QFile std_file(path);
        if(std_file.exists())
        {
            if(!std_file.open(QFile::ReadOnly|QFile::Text))
            {
                SendErrorMessage("Could not open: "+ path);
                return default_settings;
            }
            QString settings=std_file.readAll();
            std_file.close();
            return settings;
        }
        else
        {
            WriteDefaultsToStdConfig(std_file,default_settings);
            return default_settings;
        }
     }

    QDir Settings::OpenConfigDirectory()
    {
        // please give me the location in which
        // I can save my config files.
        // This location is platform independent.
        QDir config_dir(QStandardPaths::writableLocation(
                            QStandardPaths::ConfigLocation));
        // if the location is empty you should handle it.
        // Not shown here.
        if(!config_dir.exists()) // make sure the path really exists
        {
            QDir dir;
            dir.mkpath(config_dir.path()); // make all leading folder in the path.
                                           // You should check if it works fine or not. Not shown here
        }

        return config_dir;
    }

    void Settings::WriteDefaultsToStdConfig(QFile &stdConfigFile,
                                            const QString &settings)
    {
        int length = settings.length();
        if(!stdConfigFile.open(QFile::WriteOnly|QFile::Text))
        {
            SendErrorMessage("Could not open file to write -"+ stdConfigFile.fileName());
        }
        auto bytes_written = stdConfigFile.write(qPrintable(settings),length);
        if(bytes_written != length)
        {
            SendErrorMessage("Could not wite the settings to -"+stdConfigFile.fileName());
            if(!stdConfigFile.remove())
            {
                SendErrorMessage("Could not remove configuration file. Please delete remove file manually -" +
                                 stdConfigFile.fileName());
            }
        }
        stdConfigFile.close();

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
        // just to show how to use model
        auto index = m_modelCommands.index(PW_CMD_INDEX);
        auto test_cmd =m_modelCommands.data(index,Qt::DisplayRole);
        qDebug()<<"Test command the hard way"<<test_cmd.toString();

        // in this example this is a simpler way!
        if(PW_CMD_INDEX<cmd_list.size())
        {
            m_pwCommand=cmd_list[PW_CMD_INDEX];
        }
        else
        {
            emit NotifyStatusMessage("unable to get pulse width commands");
        }
    }



}
