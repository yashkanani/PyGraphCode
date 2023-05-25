#ifndef CONTAINER_INFORMATION_H
#define CONTAINER_INFORMATION_H

#include "AbstractElement.h"
#include <QList>

enum class ElementType {
    ELEMENT,
    PARENT
};

typedef struct ContainerInformation {
    ElementType type = ElementType::PARENT;
    AbstractElement* elementPointer;
    QList<ContainerInformation> children;
} ContainerInformation;

#endif // CONTAINER_INFORMATION_H