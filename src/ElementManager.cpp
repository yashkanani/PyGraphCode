#include "ElementManager.h"

#include "ReadVariableElement.h"
#include "WriteVariableElement.h"
#include "ForLoopElement.h"
#include "IfLoopElement.h"
#include "ConditionalElement.h"
#include "OperationElement.h"
#include "ConstantDecimalElement.h"
#include "ConstantTextElement.h"

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


