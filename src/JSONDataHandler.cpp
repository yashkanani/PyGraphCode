#include "JSONDataHandler.h"
#include "AbstractElement.h"
#include "BuilderContainer.h"
#include "ElementManager.h"
#include "ElementUserInputs.h"
#include "UserDefinedElement.h"
#include "ReadVariableElement.h"
#include "WriteVariableElement.h"
#include <QJsonArray>
#include <qfile.h>
#include <qjsondocument.h>
#include <variant>

namespace JSONSting {
const QString type = "type";
const QString element = "element";
const QString container = "container";
const QString userelement = "userElement";
const QString readElement = "readVariable";
const QString writeElement = "writeVariable";
const QString elementName = "name";
const QString elementinputs = "elementInputs";
const QString containerinputs = "containerInputs";
const QString displayName = "displayName";
const QString inputData = "inputData";
}

bool JSONDataHandler::saveContainerInformationListToJsonFile(const JSONContainerHeader& containerData, const QString& filePath) const
{
    QJsonObject rootObject;
    rootObject[JSONSting::displayName] = containerData.displayName;
    rootObject[JSONSting::inputData] = convertContainerInformationListToJson(containerData.containerinformationList);

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

        jsonObject[JSONSting::elementName] = containerInfo.elementPointer->getName();

        if (containerInfo.droppedItem == DroppedItem::ELEMENT && containerInfo.elementPointer) {

            if (containerInfo.elementPointer->getType() == BasicElementType::USER_DEFINED) {
                jsonObject[JSONSting::type] = JSONSting::userelement;
            } else if (containerInfo.elementPointer->getType() == BasicElementType::WRITE_VARIABLE) {
                jsonObject[JSONSting::type] = JSONSting::writeElement;
            } else if (containerInfo.elementPointer->getType() == BasicElementType::READ_VARIABLE) {
                jsonObject[JSONSting::type] = JSONSting::readElement;
            } 
            else {
                jsonObject[JSONSting::type] = JSONSting::element;
            }

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

JSONDataHandler::JSONContainerHeader JSONDataHandler::readContainerInformationListFromJsonFile(const QString& filePath) const
{
    JSONDataHandler::JSONContainerHeader packet;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file for reading.";
        return packet;
    }

    QString jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8());
    if (jsonDocument.isNull()) {
        qDebug() << "Failed to parse JSON document.";
        return packet;
    }

    QJsonObject rootObject = jsonDocument.object();
    QString displayName = rootObject.value(JSONSting::displayName).toString();

    // Process the inputData value as needed
    QJsonValue inputDataValue = rootObject.value(JSONSting::inputData);
    if (inputDataValue.isObject()) {
        QJsonObject inputDataObject = inputDataValue.toObject();

        //fill packet information
        packet.displayName = displayName;
        packet.containerinformationList = convertJsonToContainerInformationList(inputDataObject);
        return packet;
    }

    return packet;
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
                    if (containerInfoObject.contains(JSONSting::type)) {
                        QString elementType = containerInfoObject[JSONSting::type].toString();
                        if (elementType == JSONSting::element) {
                            containerInfo.elementPointer = ElementManager::getInstance().createElementFromName(elementName);
                        } 
                        else if (elementType == JSONSting::readElement) {
                            containerInfo.elementPointer = std::make_shared<ReadVariableElement>();
                            containerInfo.elementPointer->setName(elementName);
                        } 
                        else if (elementType == JSONSting::writeElement) {
                            containerInfo.elementPointer = std::make_shared<WriteVariableElement>();
                            containerInfo.elementPointer->setName(elementName);
                        }
                        else if (elementType == JSONSting::userelement)
                        {
                            containerInfo.elementPointer = std::make_shared<UserDefinedElement>();
                            containerInfo.elementPointer->setName(elementName);
                        }
                    }

                    // Check if elementPointer is empty
                    if (containerInfo.elementPointer == nullptr) {
                        continue; // Move to the next element in the loop
                    }

                    containerInfo.droppedItem = DroppedItem::ELEMENT;
                    std::shared_ptr<ElementUserInputs> inputHandler = std::make_shared<ElementUserInputs>();

                    for (const QString& key : inputsObject.keys()) {
                        QJsonValue value = inputsObject.value(key);

                        if (value.isString()) {
                            QString inputValue = value.toString();
                            inputHandler->addString(key.toStdString(), inputValue);
                        } else if (value.isObject()) {
                            ContainerInformationList subContainerList = convertJsonToContainerInformationList(value.toObject());
                            std::shared_ptr<BuilderContainer> subContainer = std::make_shared<BuilderContainer>(nullptr, true);
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