#ifndef JSON_DATA_HANDLER_H
#define JSON_DATA_HANDLER_H

#include "ContainerInformation.h"
#include <QJsonObject>

class JSONDataHandler {
public:
    ContainerInformationList readContainerInformationListFromJsonFile(const QString& filePath) const;
    bool saveContainerInformationListToJsonFile(const ContainerInformationList& containerList, const QString& filePath) const;

private:
    QJsonObject convertContainerInformationListToJson(const ContainerInformationList& containerList) const;
    ContainerInformationList convertJsonToContainerInformationList(const QJsonObject& jsonObject) const;
};

#endif // JSON_DATA_HANDLER_H