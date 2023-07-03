#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include <vector>
#include <memory>
#include "ContainerInformation.h"
#include "BasicElementType.h"

class AbstractElement;
class ElementManager {
public:
    static ElementManager& getInstance();

    std::vector<AbstractElement*> getAllElements();
    
    
    std::shared_ptr<AbstractElement> createElementFromName(const QString& elementName);
   
    std::shared_ptr<AbstractElement> createCustomElement(const ContainerInformationList& informationList);

private:
    ElementManager();

    ElementManager(const ElementManager&) = delete;
    ElementManager& operator=(const ElementManager&) = delete;

    void createElements();

    std::vector<std::shared_ptr<AbstractElement>> elements;
    std::vector<std::shared_ptr<AbstractElement>> customElementsList;

    std::shared_ptr<AbstractElement> findElementFromType(const BasicElementType& elementType);
    std::shared_ptr<AbstractElement> findElementFromName(const QString& elementName);
    std::shared_ptr<AbstractElement> createElementFromType(const BasicElementType& elementType);
    void addCustomElement(std::shared_ptr<AbstractElement>);
};

#endif  // ELEMENT_MANAGER_H