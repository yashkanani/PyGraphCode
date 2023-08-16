#include "DeleteItem.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qscrollbar.h>


#include "AbstractElement.h"

DeleteItem::DeleteItem(const QString& closeImage, const QString& openImage,QWidget* parent)
    : QWidget(parent)
{
    isDustbinOpen = false;

    setAcceptDrops(true); // Enable drag-and-drop events

    closePixmap.load(closeImage);
    openPixmap.load(openImage);

    setFixedSize(closePixmap.size());
}

void DeleteItem::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    const QVariant& elementPointer = mimeData->property("element");
    if (elementPointer.isValid()) {
        isDustbinOpen = true;
        update();
        event->acceptProposedAction();
    }
    event->accept(); // Prevent event propagation to parent widget
}

void DeleteItem::dragMoveEvent(QDragMoveEvent* event)
{
    event->acceptProposedAction();
    event->accept(); // Prevent event propagation to parent widget
}

void DeleteItem::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    const QVariant& elementPointer = mimeData->property("element");
    if (elementPointer.isValid()) {
        AbstractElement* element = qvariant_cast<AbstractElement*>(elementPointer);
        if (element) {
            event->acceptProposedAction();
        }
    }

    isDustbinOpen = false;
    update();
    event->accept(); // Prevent event propagation to parent widget
}

void DeleteItem::dragLeaveEvent(QDragLeaveEvent* event)
{
    isDustbinOpen = false;
    update();
    event->accept(); // Prevent event propagation to parent widget
}

void DeleteItem::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (isDustbinOpen) {
        painter.drawPixmap(0, 0, openPixmap);
    } else {
        painter.drawPixmap(0, 0, closePixmap);
    }
}

