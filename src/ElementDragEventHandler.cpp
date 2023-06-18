#include "ElementDragEventHandler.h"

#include "AbstractElement.h"

#include <qevent.h>
#include <qlabel.h>
#include <qdrag.h>
#include <qmimedata.h>


bool ElementDragEventHandler::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QWidget* label = qobject_cast<QWidget*>(watched);
        if (label && label->property("element").isValid()) {

            // Get the element data stored in the label
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
            drag->exec(Qt::CopyAction | Qt::MoveAction);
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}