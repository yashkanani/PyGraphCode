#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include <vector>
#include <memory>
#include "AbstractElement.h"
#include "VariableElement.h"
#include "ForLoopElement.h"
#include "IfLoopElement.h"
#include "ConditionalElement.h"

class ElementManager {
public:
    static ElementManager& getInstance();

    std::vector<AbstractElement*> getAllElements();

private:
    ElementManager();

    ElementManager(const ElementManager&) = delete;
    ElementManager& operator=(const ElementManager&) = delete;

    void createElements();

    std::vector<std::unique_ptr<AbstractElement>> elements;
};

#endif  // ELEMENT_MANAGER_H