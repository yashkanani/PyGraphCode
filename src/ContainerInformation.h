#ifndef CONTAINER_INFORMATION_H
#define CONTAINER_INFORMATION_H

#include <QList>

class AbstractElement;
class BuilderContainer;

enum class DroppedItem {
    ELEMENT,
    CONTAINER,
    PARENT
};

typedef struct ContainerInformation {
    DroppedItem droppedItem = DroppedItem::PARENT;
    std::shared_ptr<AbstractElement> elementPointer;
    std::shared_ptr <BuilderContainer> containerPointer;
    QList<ContainerInformation> children;
} ContainerInformation;

#endif // CONTAINER_INFORMATION_H