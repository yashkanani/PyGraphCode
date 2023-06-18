#include "InternalDragEventHandler.h"
#include "BuilderContainer.h" 
#include "AbstractElement.h"

#include <qevent.h>
#include <qlabel.h>
#include <qdrag.h>
#include <qmimedata.h>

InternalDragEventHandler::InternalDragEventHandler(QObject* parent)
    : QObject(parent)
    
{
}

bool InternalDragEventHandler::eventFilter(QObject* watched, QEvent* event)
{
    QWidget* label = qobject_cast<QWidget*>(watched);
    if (label && event->type() == QEvent::MouseButtonPress) {
        if (label->property("element").isValid()) {
            AbstractElement* element = qvariant_cast<AbstractElement*>(label->property("element"));

            // Create a drag object
            QDrag* drag = new QDrag(label);
            QMimeData* mimeData = new QMimeData;

            // Set the element as the mime data
            mimeData->setProperty("element", QVariant::fromValue(element));

            drag->setMimeData(mimeData);

            // Set the drag pixmap
            QPixmap pixmap = element->getImage().scaled(90, 90); // Adjust the size as needed
            drag->setPixmap(pixmap);

            // Start the drag
            if (drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction) {
                // Remove the dragged element from containerInformation
                BuilderContainer* builderContainer = dynamic_cast<BuilderContainer*>(parent());
                if (builderContainer) {
                    builderContainer->removeElementFromContainerInformation(element);
                }
            }

            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}