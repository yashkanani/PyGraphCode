#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include <vector>
#include <memory>
#include "AbstractElement.h"


class ElementManager {
public:
    static ElementManager& getInstance();

    std::vector<AbstractElement*> getAllElements();
    AbstractElement* findElementByName(const QString& name);

private:
    ElementManager();

    ElementManager(const ElementManager&) = delete;
    ElementManager& operator=(const ElementManager&) = delete;

    void createElements();

    std::vector<std::shared_ptr<AbstractElement>> elements;
};

#endif  // ELEMENT_MANAGER_H