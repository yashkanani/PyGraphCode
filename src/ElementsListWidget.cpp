#include "ElementsListWidget.h"
#include "AbstractElement.h"
#include "ElementDragEventHandler.h"
#include <QAbstractScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QVariant>

ElementsListWidget::ElementsListWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* mainlayout = new QVBoxLayout(this);
    mainlayout->setContentsMargins(0, 0, 0, 0);

    QWidget* wdg = new QWidget(this);
    wdg->setObjectName("ElementsListWidget");
   
    QVBoxLayout* layout = new QVBoxLayout(wdg);
    layout->setContentsMargins(0, 0, 0, 0);

    QScrollArea* scrollArea = new QScrollArea(wdg);
    scrollArea->setObjectName("ElementListScrollArea");
    scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    scrollArea->setWidgetResizable(true);

    QWidget* elementsListHolder = new QWidget(scrollArea);
    elementsListHolder->setObjectName("ElementsListHolder");
    elementsListLayout = new QGridLayout(elementsListHolder);
    /*elementsListLayout->setContentsMargins(10, 10, 10, 10);
    elementsListLayout->setSpacing(10);*/

    scrollArea->setWidget(elementsListHolder);

    layout->addWidget(scrollArea);

    mainlayout->addWidget(wdg);
    setLayout(mainlayout);

    elementsPerRow = 3;
}

void ElementsListWidget::addElement(AbstractElement* element)
{

    // Add the element icon label to the grid layout at the appropriate position
    QWidget* elementDispalyWidget = new QWidget(this);
    elementDispalyWidget->setObjectName("elementDisplayUnit");

    QVBoxLayout* elementdisplayLay = new QVBoxLayout(elementDispalyWidget);
    elementdisplayLay->setContentsMargins(0, 0, 0, 0);

    QLabel* elementIconLabel = new QLabel(elementDispalyWidget);
    elementIconLabel->setObjectName("elementIconLabel");
    elementIconLabel->setAlignment(Qt::AlignCenter);
    /*elementIconLabel->setStyleSheet("QLabel:hover { background-color: lightgray; }");*/
    elementIconLabel->setProperty("element", QVariant::fromValue(static_cast<AbstractElement*>(element)));
    elementIconLabel->setCursor(Qt::OpenHandCursor);
    elementIconLabel->setAlignment(Qt::AlignCenter);
    elementIconLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    elementIconLabel->installEventFilter(new ElementDragEventHandler(elementIconLabel)); // Install event filter
    elementIconLabel->setPixmap(element->getImage().scaled(50, 50));


    QLabel* elementNameLabel = new QLabel(element->getName(), elementDispalyWidget);
    elementNameLabel->setObjectName("elementNameLabel");
    elementNameLabel->setAlignment(Qt::AlignCenter);
    elementNameLabel->setWordWrap(true);

    // Calculate the row and column count for the new element
    int rowCount = elementsListLayout->count() / elementsPerRow;
    int columnCount = elementsListLayout->count() % elementsPerRow;

    // Remove the stretch from the last row and col
    elementsListLayout->setRowStretch(rowCount, 0);
    elementsListLayout->setColumnStretch(columnCount, 0);


    elementdisplayLay->addWidget(elementIconLabel);
    elementdisplayLay->addWidget(elementNameLabel);
    elementdisplayLay->addStretch();

    elementsListLayout->addWidget(elementDispalyWidget, rowCount, columnCount);
    rowCount++;
    columnCount++;

    // Add the stretch to the new last row and col
    elementsListLayout->setRowStretch(rowCount, 1);
    elementsListLayout->setColumnStretch(columnCount, 1);
}

void ElementsListWidget::setElementsPerRow(int numberOfelementsPerRow)
{
    if (numberOfelementsPerRow > 0) {
        elementsPerRow = numberOfelementsPerRow;
    }
}
