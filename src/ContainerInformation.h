#ifndef CONTAINER_INFORMATION_H
#define CONTAINER_INFORMATION_H

#include <QList>

class AbstractElement;
class BuilderContainer;

enum class ElementType {
    ELEMENT,
    CONTAINERS
};

typedef struct ContainerInformation {
    ElementType type = ElementType::CONTAINERS;
    AbstractElement* elementPointer;
    QList<ContainerInformation> children;
} ContainerInformation;

#endif // CONTAINER_INFORMATION_H