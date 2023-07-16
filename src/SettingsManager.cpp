#include "SettingsManager.h"
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>

SettingsManager* SettingsManager::instance()
{
    static SettingsManager instance;
    return &instance;
}

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent)
{
    m_settingsFilePath = getSettingsFilePath();
    readSettingsFile();
}

SettingsManager::~SettingsManager()
{
    writeSettingsFile();
}

void SettingsManager::setValue(const QString& key, const QVariant& value)
{
    m_settingsMap[key] = value;
}

QVariant SettingsManager::getValue(const QString& key, const QVariant& defaultValue) const
{
    if (m_settingsMap.contains(key)) {
        return m_settingsMap[key];
    }

    return defaultValue;
}

QString SettingsManager::getSettingsFilePath() const
{
    QString settingsDirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(settingsDirPath); // Create the directory if it doesn't exist
    return QDir(settingsDirPath).filePath("settings.json");
}

void SettingsManager::readSettingsFile()
{
    QFile file(m_settingsFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Handle the error case
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDocument.object();
    m_settingsMap = jsonObject.toVariantMap();
}

void SettingsManager::writeSettingsFile() const
{
    QFile file(m_settingsFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Handle the error case
        return;
    }

    QJsonObject jsonObject = QJsonObject::fromVariantMap(m_settingsMap);
    QJsonDocument jsonDocument(jsonObject);

    file.resize(0); // Clear the file contents
    file.write(jsonDocument.toJson());
    file.close();
}
