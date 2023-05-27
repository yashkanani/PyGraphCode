#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <qpushbutton.h>

#include "BuilderContainer.h"
#include "ElementManager.h"

BuilderContainer::BuilderContainer(QWidget* parent) : QWidget(parent) {
    
    setAcceptDrops(true);
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    
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
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasFormat("application/element")) {
        
        QByteArray data = mimeData->data("application/element");
        if (data.isEmpty()) {
            return; 
        }

        QDataStream stream(&data, QIODevice::ReadOnly);

        QString elementName;
        stream >> elementName;

        AbstractElement* element = createInstance(elementName);
       
        if (element && isDropAccepted(element)) {
            addElement(element);
            event->acceptProposedAction();
        }
    }
}

AbstractElement* BuilderContainer::createInstance(const QString& elementName) {
    AbstractElement* elementPointer = ElementManager::getInstance().findElementByName(elementName);
    return elementPointer;
}

bool BuilderContainer::isDropAccepted(const AbstractElement* element) const {
   

    return true; // Return true if the drop is accepted, false otherwise
}

void BuilderContainer::addElement( AbstractElement* element) {
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
    auto dd = element->getName();
    auto wdg = element->getViewWidget();
    if (wdg) {
        layout->addWidget(wdg);
    }
  
}