#ifndef CONTAINER_INFORMATION_H
#define CONTAINER_INFORMATION_H

#include <QList>

class AbstractElement;
class BuilderContainer;

enum class ElementType {
    ELEMENT,
    CONTAINER,
    PARENT
};

typedef struct ContainerInformation {
    ElementType type = ElementType::PARENT;
    AbstractElement* elementPointer;
    BuilderContainer* containerPointer;
    QList<ContainerInformation> children;
} ContainerInformation;

#endif // CONTAINER_INFORMATION_H