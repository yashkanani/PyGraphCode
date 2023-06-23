#include "InternalDragEventHandler.h"
#include "AbstractElement.h"
#include "BuilderContainer.h"

#include <qdrag.h>
#include <qevent.h>
#include <qlabel.h>
#include <qmimedata.h>

InternalDragEventHandler::InternalDragEventHandler(QObject* parent)
    : QObject(parent)

{
}

bool InternalDragEventHandler::eventFilter(QObject* watched, QEvent* event)
{
    QWidget* draggedWidget = qobject_cast<QWidget*>(watched);
    if (draggedWidget && (draggedWidget->property("element").isValid()) && event->type() == QEvent::MouseButtonPress) {
        
            AbstractElement* element = qvariant_cast<AbstractElement*>(draggedWidget->property("element"));

            // Create a drag object
            QDrag* drag = new QDrag(draggedWidget);
            QMimeData* mimeData = new QMimeData;

            // Set the element as the mime data
            mimeData->setProperty("element", QVariant::fromValue(element));

            drag->setMimeData(mimeData);

            // Set the drag pixmap
            QPixmap pixmap = element->getImage().scaled(90, 90); // Adjust the size as needed
            drag->setPixmap(pixmap);

            // Start the drag
            if (drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction) {
               
                QObject* target = drag->target();

                if (target) {

                    // If the dragged element is placed inside the child container of the dragged element,
                    // we don't want to remove the dragged element. Otherwise, all elements, including the new element, will be removed.
                    BuilderContainer* targetContainer = dynamic_cast<BuilderContainer*>(target); 
                    if (draggedWidget->isAncestorOf(targetContainer)) {
                        return true;
                    }

                    // Remove the dragged element from containerInformation
                    BuilderContainer* sourceContainer = dynamic_cast<BuilderContainer*>(parent());

                    if (sourceContainer) {
                        sourceContainer->removeElementFromContainerInformation(element);
                    }
                    
                }
            }

            return true;
        
    }
  
    return QObject::eventFilter(watched, event);
}