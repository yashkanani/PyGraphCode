#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QVBoxLayout>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qpainterpath.h>

#include "BuilderContainer.h"
#include "ElementManager.h"
#include "CodeText.h"

BuilderContainer::BuilderContainer(QWidget* parent, bool isSubContainer)
    : QFrame(parent)
{
    setMaxElements(std::numeric_limits<int>::max()); // Set default value to maximum int value
    setAcceptDrops(true);
    builderContainerlayout = new QVBoxLayout(this);
    builderContainerlayout->addStretch(1);
    builderContainerlayout->setSpacing(25);
    setLayout(builderContainerlayout);

    if (isSubContainer) {
        setObjectName("BuilderContainerWidget");
        setStyleSheet(
            "QWidget#BuilderContainerWidget {"
            "   border: 1px solid black;"
            "   border-radius: 5px;"
            "}"
        );
        
    }
    
    containerInformation.droppedItem = DroppedItem::PARENT;
}

std::shared_ptr<CodeText> BuilderContainer::getText(int indentLevel) const
{
    return getText(containerInformation, indentLevel);
}

std::shared_ptr<CodeText> BuilderContainer::getText(const ContainerInformation& containerInfo, int indentLevel) const
{
    std::shared_ptr<CodeText> result = std::make_shared<CodeText>(indentLevel);
    switch (containerInfo.droppedItem) {

    case DroppedItem::ELEMENT:
        // Call the getText() method of the AbstractElement
        if (containerInfo.elementPointer)
            result = containerInfo.elementPointer->getText(indentLevel);
        break;

    case DroppedItem::CONTAINER:
        // Call the getText() method of the BuilderContainer
        if (containerInfo.containerPointer)
            result = containerInfo.containerPointer->getText(indentLevel);
        break;

    case DroppedItem::PARENT:
        // Call the getText() method recursively for each child container
        for (const auto& child : containerInfo.children) {
            std::shared_ptr<CodeText> childResult = getText(child, indentLevel);

            if (childResult) {
                if (&child != &containerInfo.children.front()) {
                    result->addToBody("\n");
                }
                result->append(*childResult);
            }
        }
        break;

    default:
        break;
    }
    return result;
}

 void BuilderContainer::setAcceptedTypes(const QList<BasicElementType>& acceptedTypesList)
{
     acceptedTypes = acceptedTypesList;
 }

void BuilderContainer::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasFormat("application/element")) {

        QByteArray data = mimeData->data("application/element");

        if (data.isEmpty() || isMaxElementsReached()) {
            event->ignore();
            return;
        }

        QDataStream stream(&data, QIODevice::ReadOnly);

        QString elementName;
        stream >> elementName;

        quint32 elementTypeValue;
        stream >> elementTypeValue;
        BasicElementType elementType = static_cast<BasicElementType>(elementTypeValue);
    
        if (isDropAccepted(elementType)) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }

}


void BuilderContainer::setMaxElements(int maxElements)
{
    this->maxElements = maxElements;
}

bool BuilderContainer::isMaxElementsReached() const
{
    if (maxElements >= 0 && containerInformation.children.size() >= maxElements) {
        return true;
    }
    return false;
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

    drawArrows();
}

void BuilderContainer::drawArrows()
{

    for (int indexOfWidget = 1; indexOfWidget < builderContainerlayout->count(); indexOfWidget++) {
        QWidget* widget = builderContainerlayout->itemAt(indexOfWidget)->widget();

        if (widget == nullptr) {
            continue;
        }

        QRect rect = widget->rect();
        int spacing = builderContainerlayout->spacing();
        QPoint pos = widget->pos();

        QPoint startPoint;
        startPoint.setX(pos.x() + rect.width() / 2);
        startPoint.setY(pos.y() - spacing + 1);

        QPoint endPoint;
        endPoint.setX(pos.x() + rect.width() / 2);
        endPoint.setY(pos.y() - 5);

        QLine line(startPoint, endPoint);

        QPainter painter(this);
        painter.setPen(QPen(QColor("#8c8c8c"), 2));
        painter.drawLine(line);
        
        int arrowHeight = 10; // Height of the arrow
        int arrowWidth = 10; // Width of the arrow

        int arrowX = endPoint.x() - (arrowWidth / 2);
        int arrowY = endPoint.y();

        QPainterPath arrowPath;
        arrowPath.moveTo(arrowX, arrowY);
        arrowPath.lineTo(arrowX + arrowWidth, arrowY);
        arrowPath.lineTo(arrowX + (arrowWidth / 2), arrowY + arrowHeight);
        arrowPath.lineTo(arrowX, arrowY);
        painter.fillPath(arrowPath, QColor("#8c8c8c"));
    
    
    
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

        quint32 elementTypeValue;
        stream >> elementTypeValue;
        BasicElementType elementType = static_cast<BasicElementType>(elementTypeValue);


        std::shared_ptr<AbstractElement> element = createInstance(elementType, elementName);
        

        if (element) {

            int insertIndex = findInsertIndex(event);

            addElementWidget(element->getViewWidget(), insertIndex);
            connect(element.get(), &AbstractElement::childValueChanged, this, &BuilderContainer::updateResultedTextView);

            ContainerInformation info;
            info.droppedItem = DroppedItem::ELEMENT;
            info.elementPointer = element;

            containerInformation.children.insert(insertIndex, info);

            hideDropIndicator(); // Hide the drop indicator
            
            emit updateResultedTextView(); // Update the text in ResultedTextView Widget.

            event->acceptProposedAction();
        }
    }
}

std::shared_ptr<AbstractElement> BuilderContainer::createInstance(const BasicElementType& elementType, const QString& elementName)
{
    std::shared_ptr<AbstractElement> elementPointer = ElementManager::getInstance().createElementFromType(elementType);
    elementPointer->setName(elementName);

    return elementPointer;
}


bool BuilderContainer::isDropAccepted(const BasicElementType& elementType) const
{
    if (acceptedTypes.isEmpty()) {
        return true; // Accept all types if acceptedTypes is empty
    }
    return acceptedTypes.contains(elementType);
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
            /*QPoint widgetCenter = widget->mapToGlobal(widget->rect().center());
            int widgetVerticalPos = widgetCenter.y();
            if (dropPos.y() < widgetVerticalPos) {
                insertIndex = builderContainerlayout->indexOf(widget);
                break;
            }*/

            QRect widgetRect = widget->geometry();
            QPoint widgetCenter = widgetRect.center();

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