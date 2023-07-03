#include "ElementManager.h"

#include "ReadVariableElement.h"
#include "WriteVariableElement.h"
#include "ForLoopElement.h"
#include "IfLoopElement.h"
#include "ConditionalElement.h"
#include "OperationElement.h"
#include "ConstantDecimalElement.h"
#include "ConstantTextElement.h"
#include "UserDefinedElement.h"
#include "ElementUserInputs.h"

#include "AbstractElement.h"

ElementManager& ElementManager::getInstance()
{
    static ElementManager instance;
    return instance;
}

ElementManager::ElementManager()
{
    createElements();
}

std::vector<AbstractElement*> ElementManager::getAllElements()
{
    std::vector<AbstractElement*> allElements;
    allElements.reserve(elements.size());
    for (const auto& element : elements) {
        allElements.push_back(element.get());
    }
    return allElements;
}

std::shared_ptr<AbstractElement> ElementManager::findElementFromType(const BasicElementType& elementType)
{
    // Check prebuild elements
    for (const auto& element : elements) {
        if (element->getType() == elementType) {
            return element;
        }
    }
    return nullptr;
}
std::shared_ptr<AbstractElement> ElementManager::findElementFromName(const QString& elementName)
{
    // Check In Basic Elements list.
    for (const auto& element : elements) {
        if (element->getName() == elementName) {
            return element;
        }
    }

    return nullptr;

}

void ElementManager::createElements()
{
    elements.push_back(std::make_shared<ReadVariableElement>());
    elements.push_back(std::make_shared<WriteVariableElement>());
    elements.push_back(std::make_shared<ForLoopElement>());
    elements.push_back(std::make_shared<IfLoopElement>());
    elements.push_back(std::make_shared<ConditionalElement>());
    elements.push_back(std::make_shared<OperationElement>());
    elements.push_back(std::make_shared<ConstantTextElement>());
    elements.push_back(std::make_shared<ConstantDecimalElement>());
}


std::shared_ptr<AbstractElement> ElementManager::createElementFromType(const BasicElementType& elementType)
{
    std::shared_ptr<AbstractElement> foundElement = findElementFromType(elementType);
    if (foundElement) {
        return foundElement->clone();
    }
    return nullptr;
}
std::shared_ptr<AbstractElement> ElementManager::createElementFromName(const QString& elementName)
{
    std::shared_ptr<AbstractElement> foundElement = findElementFromName(elementName);
    if (foundElement) {
        return foundElement->clone();
    }
    return nullptr;
}


void ElementManager::addCustomElement(std::shared_ptr<AbstractElement> customElement) {
    if (customElement != nullptr) {
        customElementsList.push_back(customElement);
    }
}

std::shared_ptr<AbstractElement> ElementManager::createCustomElement(const QString& elementName, const ContainerInformationList& informationList)
{

    std::shared_ptr<UserDefinedElement> customElement = std::make_shared<UserDefinedElement>();
    customElement->setName(elementName);

    std::shared_ptr<ElementUserInputs> userInput = std::make_shared<ElementUserInputs>();
    std::shared_ptr<BuilderContainer> builder = std::make_shared<BuilderContainer>(nullptr, true);
    
    builder->appendContainerInformationList(informationList);
    userInput->addContainer(customElement->getUserInputkey(), builder);
    customElement->setUserInput(userInput);

    addCustomElement(customElement);
    return customElement;
}
