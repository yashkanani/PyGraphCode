#include "JSONDataHandler.h"
#include <QJsonArray>
#include "AbstractElement.h"
#include "ElementUserInputs.h"
#include "BuilderContainer.h"
#include "ElementManager.h"
#include <variant>
#include <qfile.h>
#include <qjsondocument.h>

namespace JSONSting {
const QString type = "type";
const QString element = "element";
const QString container = "container";
const QString elementName = "name";
const QString elementinputs = "elementinputs";
const QString containerinputs = "containerinputs";
}

bool JSONDataHandler::saveContainerInformationListToJsonFile(const ContainerInformationList& containerList, const QString& filePath) const
{
    QJsonObject rootObject = convertContainerInformationListToJson(containerList);
    QJsonDocument jsonDocument(rootObject);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream textStream(&file);
        textStream << jsonString;
        file.close();
        qDebug() << "JSON data written to file successfully.";
        return true;
    } else {
        qDebug() << "Failed to open the file for writing.";
        return false;
    }
}


QJsonObject JSONDataHandler::convertContainerInformationListToJson(const ContainerInformationList& containerList) const
{
    QJsonArray jsonArray;

    for (const auto& containerInfo : containerList) {
        QJsonObject jsonObject;
        jsonObject[JSONSting::type] = JSONSting::element;
        jsonObject[JSONSting::elementName] = containerInfo.elementPointer->getName();

        if (containerInfo.droppedItem == DroppedItem::ELEMENT && containerInfo.elementPointer) {
            std::shared_ptr<ElementUserInputs> inputHanlder = containerInfo.elementPointer->getUserInput();
            QJsonObject inputsObject; // Create a new object for storing inputs

            for (const auto& pair : inputHanlder->getAllUserInputs()) {
                if (auto value = std::get_if<QString>(&pair.second)) {
                    inputsObject[QString::fromStdString(pair.first)] = *value;
                }
                if (auto container = std::get_if<std::shared_ptr<BuilderContainer>>(&pair.second)) {
                    inputsObject[QString::fromStdString(pair.first)] = convertContainerInformationListToJson((*container)->getContainerInformation());
                }
            }

            jsonObject[JSONSting::elementinputs] = inputsObject; // Save inputs in jsonObject
        }

        jsonArray.append(jsonObject);
    }

    QJsonObject rootObject;
    rootObject[JSONSting::type] = JSONSting::container;
    rootObject[JSONSting::containerinputs] = jsonArray;

    return rootObject;
}


ContainerInformationList JSONDataHandler::readContainerInformationListFromJsonFile(const QString& filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file for reading.";
        return ContainerInformationList();
    }

    QString jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8());
    if (jsonDocument.isNull()) {
        qDebug() << "Failed to parse JSON document.";
        return ContainerInformationList();
    }

    QJsonObject rootObject = jsonDocument.object();
    return convertJsonToContainerInformationList(rootObject);
}


ContainerInformationList JSONDataHandler::convertJsonToContainerInformationList(const QJsonObject& jsonObject) const
{
    ContainerInformationList containerList;

    if (jsonObject.contains(JSONSting::containerinputs) && jsonObject[JSONSting::containerinputs].isArray()) {
        QJsonArray jsonArray = jsonObject[JSONSting::containerinputs].toArray();

        for (const auto& jsonValue : jsonArray) {
            if (jsonValue.isObject()) {
                QJsonObject containerInfoObject = jsonValue.toObject();

                if (containerInfoObject.contains(JSONSting::elementName) && containerInfoObject.contains(JSONSting::elementinputs)) {
                    QString elementName = containerInfoObject[JSONSting::elementName].toString();
                    QJsonObject inputsObject = containerInfoObject[JSONSting::elementinputs].toObject();

                    ContainerInformation containerInfo;
                    containerInfo.elementPointer = ElementManager::getInstance().createElementFromName(elementName);

                    // Check if elementPointer is empty
                    if (containerInfo.elementPointer == nullptr) {
                        continue; // Move to the next element in the loop
                    }

                    std::shared_ptr<ElementUserInputs> inputHandler = std::make_shared<ElementUserInputs>();

                    for (const QString& key : inputsObject.keys()) {
                        QJsonValue value = inputsObject.value(key);

                        if (value.isString()) {
                            QString inputValue = value.toString();
                            inputHandler->addString(key.toStdString(), inputValue);
                        } else if (value.isObject()) {
                            ContainerInformationList subContainerList = convertJsonToContainerInformationList(value.toObject());
                            std::shared_ptr<BuilderContainer> subContainer = std::make_shared<BuilderContainer>();
                            subContainer->appendContainerInformationList(subContainerList);
                            inputHandler->addContainer(key.toStdString(), subContainer);
                        }
                    }

                    containerInfo.elementPointer->setUserInput(inputHandler);
                    containerList.push_back(containerInfo);
                }
            }
        }
    }

    return containerList;
}