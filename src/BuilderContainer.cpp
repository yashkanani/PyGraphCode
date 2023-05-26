#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <qpushbutton.h>

#include "BuilderContainer.h"

BuilderContainer::BuilderContainer(QWidget* parent) : QWidget(parent) {
    
    setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    layout->addWidget(new QPushButton("hello"));
}

QString BuilderContainer::getText() const
{
    return getText(containerInformation);
}

QString BuilderContainer::getText(const ContainerInformation& containerInfo) const
{
    QString result;
    switch (containerInfo.type) {
    
    case ElementType::ELEMENT:
        // Call the getText() method of the AbstractElement
        if (containerInfo.elementPointer)
            result = containerInfo.elementPointer->getText();
        break;
    
    case ElementType::CONTAINERS:
        // Call the getText() method recursively for each child container
        for (BuilderContainer* childContainer : containerInfo.children)
            result += childContainer->getText(childContainer->containerInformation);
        break;
    default:
        break;
    }
    return result;
}


void BuilderContainer::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/element")) {
        event->acceptProposedAction();
    }
}

void BuilderContainer::dragMoveEvent(QDragMoveEvent* event) {
    if (event->mimeData()->hasFormat("application/element")) {
        event->acceptProposedAction();
    }
}

void BuilderContainer::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasFormat("application/element")) {
        QByteArray data = event->mimeData()->data("application/element");
        QDataStream stream(&data, QIODevice::ReadOnly);

        QString elementType;
        stream >> elementType;

        AbstractElement* element = createInstance(elementType);
        if (element && isDropAccepted(element)) {
            addElement(element);
            event->acceptProposedAction();
        }
    }
}

AbstractElement* BuilderContainer::createInstance(const QString& elementType) {
    
    return nullptr;
}

bool BuilderContainer::isDropAccepted(const AbstractElement* element) const {
   

    return true; // Return true if the drop is accepted, false otherwise
}

void BuilderContainer::addElement(AbstractElement* element) {
    // Add the element to the container
    // You can customize the layout and visual representation based on your requirements

  /*  QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
    if (layout) {
        QWidget* widget = new QWidget(this);
        layout->addWidget(widget);

        QVBoxLayout* elementLayout = new QVBoxLayout(widget);
        elementLayout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(elementLayout);

        elementLayout->addWidget(element);
    }*/
}