#ifndef JSON_DATA_HANDLER_H
#define JSON_DATA_HANDLER_H

#include "ContainerInformation.h"
#include <QJsonObject>

class JSONDataHandler {
public:
    QJsonObject convertContainerInformationListToJson(const ContainerInformationList& containerList) const;
    ContainerInformationList convertJsonToContainerInformationList(const QJsonObject& jsonObject) const;
};

#endif // JSON_DATA_HANDLER_H