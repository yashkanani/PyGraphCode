#include "ElementManager.h"

ElementManager& ElementManager::getInstance() {
    static ElementManager instance;
    return instance;
}

ElementManager::ElementManager() {
    createElements();
}

std::vector<AbstractElement*> ElementManager::getAllElements() {
    std::vector<AbstractElement*> allElements;
    allElements.reserve(elements.size());
    for (const auto& element : elements) {
        allElements.push_back(element.get());
    }
    return allElements;
}

void ElementManager::createElements() {
    elements.push_back(std::make_unique<VariableElement>());
    elements.push_back(std::make_unique<ForLoopElement>());
    elements.push_back(std::make_unique<IfLoopElement>());
    elements.push_back(std::make_unique<ConditionalElement>());
}