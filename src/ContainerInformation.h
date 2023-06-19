#ifndef CONTAINER_INFORMATION_H
#define CONTAINER_INFORMATION_H

#include <QList>

class AbstractElement;
class BuilderContainer;

enum class DroppedItem {
    UNKNOW = 0,
    ELEMENT
};

typedef struct ContainerInformation {
    DroppedItem droppedItem = DroppedItem::ELEMENT;
    std::shared_ptr<AbstractElement> elementPointer;
} ContainerInformation;

#endif // CONTAINER_INFORMATION_H