#include "ElementManager.h"

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

AbstractElement* ElementManager::findElementByName(const QString& name)
{
    for (const auto& element : elements) {
        if (element->getName() == name) {
            return element.get();
        }
    }
    return nullptr;
}

void ElementManager::createElements()
{
    elements.push_back(std::make_shared<VariableElement>());
    elements.push_back(std::make_shared<ForLoopElement>());
    elements.push_back(std::make_shared<IfLoopElement>());
    elements.push_back(std::make_shared<ConditionalElement>());
}