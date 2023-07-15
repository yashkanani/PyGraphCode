#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QVBoxLayout>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpushbutton.h>

#include "AbstractElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "InternalDragEventHandler.h"

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
            "}");
    }

    // If any changes occur in the child, the updateResultedTextView signal is emitted,
    // which helps ensure that the arrow is drawn correctly.
    // To achieve this, a paint event is generated using the update function.
    QObject::connect(this, &BuilderContainer::updateResultedTextView, this, [=]() { update(); });
}

std::shared_ptr<CodeText> BuilderContainer::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> result = std::make_shared<CodeText>(indentLevel);

    // Call the getText() method recursively for each child container
    for (const auto& child : containerInformationList) {

        if (child.droppedItem != DroppedItem::ELEMENT) {
            continue;
        }

        std::shared_ptr<CodeText> childResult = child.elementPointer->getText(indentLevel);

        if (childResult) {
            if (&child != &containerInformationList.front()) {
                result->addToBody("\n");
            }
            result->append(*childResult);
        }
    }

    return result;
}

const ContainerInformationList& BuilderContainer::getContainerInformation() const
{
    return containerInformationList;
}

void BuilderContainer::appendContainerInformationList(const ContainerInformationList& informationList, int _insertIndex)
{

    int insertIndex = _insertIndex;
    for (int i = 0; i < informationList.size(); ++i) {

        if ((informationList[i].droppedItem != DroppedItem::ELEMENT) || (informationList[i].elementPointer == nullptr)) {
            continue;
        }

        auto element = informationList[i].elementPointer->clone();
        addInformationAndView(element, insertIndex);
        ++insertIndex;
    }
    emit updateResultedTextView(); // Update the text in ResultedTextView Widget.
}

void BuilderContainer::removeElementFromContainerInformation(const AbstractElement* element)
{

    int removeIndex = -1;
    for (int i = 0; i < containerInformationList.size(); ++i) {
        if ((containerInformationList[i].droppedItem == DroppedItem::ELEMENT) && (containerInformationList[i].elementPointer.get() == element)) {
            removeIndex = i;
            break;
        }
    }

    if (removeIndex != -1) {
        containerInformationList.erase(containerInformationList.begin() + removeIndex);

        // Remove the corresponding widget from builderContainerlayout
        QWidget* widget = builderContainerlayout->itemAt(removeIndex)->widget();
        if (widget) {
            builderContainerlayout->removeWidget(widget);
            delete widget;
        }

        emit updateResultedTextView(); // Update the text in ResultedTextView Widget.
    }
}

void BuilderContainer::setAcceptedTypes(const QList<BasicElementType>& acceptedTypesList)
{
    acceptedTypes = acceptedTypesList;
}

void BuilderContainer::dragEnterEvent(QDragEnterEvent* event)
{
    if (isMaxElementsReached()) {
        event->ignore();
        return;
    }

    const QMimeData* mimeData = event->mimeData();
    const QVariant& elementPointer = mimeData->property("element");
    if (elementPointer.isValid()) {
        //std::shared_ptr<AbstractElement> element = qvariant_cast<AbstractElement*>(elementPointer)->clone();
        AbstractElement* element = qvariant_cast<AbstractElement*>(elementPointer);
        if (element && isDropAccepted(element->getType())) {
            event->acceptProposedAction();
            return;
        }
    }
    event->ignore();
}

void BuilderContainer::setMaxElements(int maxElements)
{
    this->maxElements = maxElements;
}

bool BuilderContainer::isMaxElementsReached() const
{
    if (maxElements >= 0 && containerInformationList.size() >= maxElements) {
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

    if (insertIndex >= 0 && insertIndex < builderContainerlayout->count() - 1) {
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
    if (event->mimeData()->property("element").isValid()) {
        int insertIndex = findInsertIndex(event);

        updateDropIndicator(insertIndex);


        auto pos = event->pos();

        emit EnsureVisible(pos.x(), pos.y());

        event->acceptProposedAction();
    }
}
void BuilderContainer::mousePressEvent(QMouseEvent* event)
{
    // Prevent the event from being passed to the parent widget
    event->accept();
}
void BuilderContainer::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    const QVariant& elementPointer = mimeData->property("element");
    if (elementPointer.isValid()) {
        std::shared_ptr<AbstractElement> element = qvariant_cast<AbstractElement*>(elementPointer)->clone();
        if (element) {

            int insertIndex = findInsertIndex(event);

            addInformationAndView(element, insertIndex);

            hideDropIndicator(); // Hide the drop indicator

            emit updateResultedTextView(); // Update the text in ResultedTextView Widget.

            event->acceptProposedAction();
        }
    }
}

void BuilderContainer::addInformationAndView(std::shared_ptr<AbstractElement> element, int insertIndex)
{
    if ((element == nullptr) || (insertIndex < 0)) {
        return;
    }

    connect(element.get(), &AbstractElement::childValueChanged, this, &BuilderContainer::updateResultedTextView);
    connect(element.get(), &AbstractElement::notifyToParameterWidgets, this, &BuilderContainer::notifyToParameterWidgets);

    // add element view
    QWidget* viewWidget = element->getViewWidget();
    viewWidget->setProperty("element", QVariant::fromValue(dynamic_cast<AbstractElement*>(element.get())));
    viewWidget->installEventFilter(new InternalDragEventHandler(this));
    addElementWidget(viewWidget, insertIndex);
    

    // add information
    ContainerInformation info;
    info.droppedItem = DroppedItem::ELEMENT;
    info.elementPointer = element;
    containerInformationList.insert(insertIndex, info);
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
