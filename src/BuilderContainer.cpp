#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QVBoxLayout>
#include <qpainter.h>
#include <qpushbutton.h>

#include "BuilderContainer.h"
#include "ElementManager.h"

BuilderContainer::BuilderContainer(QWidget* parent)
    : QWidget(parent)
{

    setAcceptDrops(true);
    builderContainerlayout = new QVBoxLayout(this);
    builderContainerlayout->setContentsMargins(0, 0, 0, 0);
    builderContainerlayout->addStretch(1);
    setLayout(builderContainerlayout);

    containerInformation.type = ElementType::PARENT;
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

    case ElementType::CONTAINER:
        // Call the getText() method of the BuilderContainer
        if (containerInfo.containerPointer)
            result = containerInfo.containerPointer->getText();
        break;

    case ElementType::PARENT:
        // Call the getText() method recursively for each child container
        for (auto& childContainerInfo : containerInfo.children)
            result += getText(childContainerInfo);
        break;
    default:
        break;
    }
    return result;
}

void BuilderContainer::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/element")) {
        event->acceptProposedAction();
    }
}

void BuilderContainer::dragLeaveEvent(QDragLeaveEvent* event)
{
    hideDropIndicator();
    event->accept();
}
void BuilderContainer::hideDropIndicator()
{
    isDropIndicatorVisible = false;
    update(); // Request a repaint
}
void BuilderContainer::updateDropIndicator(int insertIndex)
{
    // Calculate the drop indicator rectangle position
    dropIndicatorRect = calculateDropIndicatorRect(insertIndex);
    isDropIndicatorVisible = true;

    update(); // Request a repaint
}

void BuilderContainer::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    if (isDropIndicatorVisible) {
        QPainter painter(this);
        painter.fillRect(dropIndicatorRect, Qt::black);
    }
}

QRect BuilderContainer::calculateDropIndicatorRect(int insertIndex) const
{
    int height = 2; // Set the height of the drop indicator rectangle
    int y = 0; // Initialize the Y-coordinate

    if (insertIndex >= 0 && insertIndex < builderContainerlayout->count()-1) {
        QWidget* widget = builderContainerlayout->itemAt(insertIndex)->widget();
        if (widget) {
            QRect widgetRect = widget->geometry();
            y = widgetRect.y();
        }
    } else {
        // If insertIndex is out of range, position the drop indicator at the bottom of the container
        QLayoutItem* lastItem = builderContainerlayout->itemAt(builderContainerlayout->count() - 2); // Get the second-to-last item (excluding the stretch)
        if (lastItem) {
            QWidget* lastWidget = lastItem->widget();
            if (lastWidget) {
                QRect lastWidgetRect = lastWidget->geometry();
                y = lastWidgetRect.bottom() + 10; // Add 10 for a small space between the last element and the indicator
            }
        }
    }

    return QRect(0, y, width(), height);
}

void BuilderContainer::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasFormat("application/element")) {
        int insertIndex = findInsertIndex(event);

        updateDropIndicator(insertIndex);

        event->acceptProposedAction();
    }
}

void BuilderContainer::dropEvent(QDropEvent* event)
{
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

            int insertIndex = findInsertIndex(event);

            addElementWidget(element->getViewWidget(), insertIndex);

            ContainerInformation info;
            info.type = ElementType::ELEMENT;
            info.elementPointer = element;

            containerInformation.children.insert(insertIndex, info);

            hideDropIndicator(); // Hide the drop indicator

            event->acceptProposedAction();
        }
    }
}

AbstractElement* BuilderContainer::createInstance(const QString& elementName)
{
    AbstractElement* elementPointer = ElementManager::getInstance().findElementByName(elementName);
    return elementPointer;
}

bool BuilderContainer::isDropAccepted(const AbstractElement* element) const
{

    return true; // Return true if the drop is accepted, false otherwise
}

void BuilderContainer::addElementWidget(QWidget* elementView, int insertIndex = -1)
{
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

    // Remove existing addStretch
    QLayoutItem* stretchItem = builderContainerlayout->itemAt(builderContainerlayout->count() - 1);
    if (stretchItem != nullptr && static_cast<QSpacerItem*>(stretchItem) != nullptr) {
        builderContainerlayout->removeItem(stretchItem);
    }

    // set element horizonatally in center.
    if (elementView) {
        // set element View at second last in container layout because last element is stretch to 1.
        builderContainerlayout->insertWidget(insertIndex, elementView, 0, Qt::AlignTop | Qt::AlignHCenter);
    }

    builderContainerlayout->addItem(stretchItem);
}

int BuilderContainer::findInsertIndex(QDropEvent* event)
{
    QPoint dropPos = event->pos();

    // Find the index to insert the new label at except stretch widget
    int insertIndex = -1;
    for (int i = 0; i < builderContainerlayout->count() - 1; ++i) {
        QWidget* widget = builderContainerlayout->itemAt(i)->widget();
        if (widget) {
            QPoint widgetCenter = widget->mapToGlobal(widget->rect().center());
            int widgetVerticalPos = widgetCenter.y();
            if (dropPos.y() < widgetVerticalPos) {
                insertIndex = builderContainerlayout->indexOf(widget);
                break;
            }
        }
    }

    if (insertIndex == -1) {
        insertIndex = builderContainerlayout->count() - 1; // Drop at the end if no position found
    }
    return insertIndex;
}       