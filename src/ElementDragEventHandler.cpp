#include "ElementDragEventHandler.h"

#include "AbstractElement.h"

#include <qevent.h>
#include <qlabel.h>
#include <qdrag.h>
#include <qmimedata.h>



bool ElementDragEventHandler::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* label = qobject_cast<QLabel*>(watched);
        if (label) {
            
            // Get the element data stored in the label
            AbstractElement* element = qvariant_cast<AbstractElement*>(label->property("element"));

            // Create a drag object
            QDrag* drag = new QDrag(label);
            QMimeData* mimeData = new QMimeData;
            QByteArray data;

            QDataStream stream(&data, QIODevice::WriteOnly);
            stream << element->getName();

            mimeData->setData("application/element", data);
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