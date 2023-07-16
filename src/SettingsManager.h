#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QVariant>

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    static SettingsManager* instance();

    void setValue(const QString& key, const QVariant& value);
    QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const;

private:
    explicit SettingsManager(QObject* parent = nullptr);
    ~SettingsManager();

    QString getSettingsFilePath() const;
    void readSettingsFile();
    void writeSettingsFile() const;

    QString m_settingsFilePath;
    QMap<QString, QVariant> m_settingsMap;
};

#endif // SETTINGSMANAGER_H
