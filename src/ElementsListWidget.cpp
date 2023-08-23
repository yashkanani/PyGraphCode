#include "ElementsListWidget.h"
#include "AbstractElement.h"
#include "ElementDragEventHandler.h"
#include <QAbstractScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QSortFilterProxyModel>
#include <QVariant>
#include <qscrollbar.h>
#include <qstandarditemmodel.h>
#include <qtreeview.h>

ElementsListWidget::ElementsListWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* mainlayout = new QVBoxLayout(this);
    mainlayout->setContentsMargins(0, 0, 0, 0);

    elementsListLayout = new QTreeView(this);
    elementsListLayout->setContentsMargins(0, 0, 0, 0);
    elementsListLayout->setHeaderHidden(true);
    elementsListLayout->setIndentation(0);
    elementsListLayout->setUniformRowHeights(false);
    elementsListLayout->setObjectName("ElementsListWidget");
    elementsListLayout->setSelectionMode(QAbstractItemView::NoSelection);

    elementsListLayout->verticalScrollBar()->parent()->setProperty("background_transparent", true);
    elementsListLayout->horizontalScrollBar()->parent()->setProperty("background_transparent", true);

    sourceModel = new QStandardItemModel(this);
    elementsListLayout->setModel(sourceModel);
    
    mainlayout->addWidget(elementsListLayout);
    setLayout(mainlayout);

    elementsPerRow = 2;
    totalModelElements = 0;
    sourceModel->setColumnCount(elementsPerRow);
}

void ElementsListWidget::addElement(AbstractElement* element)
{
    elementsModel << element;
    showWidgetOnView(createDisplayUnit(element));
}

QWidget* ElementsListWidget::createDisplayUnit(AbstractElement* element)
{

    if (!element) {
        return nullptr;
    }
        

    QWidget* elementDispalyWidget = new QWidget;
    elementDispalyWidget->setObjectName("elementDisplayUnit");

    QVBoxLayout* elementdisplayLay = new QVBoxLayout(elementDispalyWidget);
    //elementdisplayLay->setContentsMargins(0, 0, 0, 0);

    QLabel* elementIconLabel = new QLabel(elementDispalyWidget);
    elementIconLabel->setObjectName("elementIconLabel");
    elementIconLabel->setProperty("element", QVariant::fromValue(static_cast<AbstractElement*>(element)));
    elementIconLabel->setCursor(Qt::OpenHandCursor);
    elementIconLabel->setAlignment(Qt::AlignCenter);
    elementIconLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    elementIconLabel->installEventFilter(new ElementDragEventHandler(elementIconLabel)); // Install event filter
    elementIconLabel->setPixmap(element->getImage().scaled(50, 50));

    QLabel* elementNameLabel = new QLabel(element->getName(), elementDispalyWidget);
    elementNameLabel->setObjectName("elementNameLabel");
    elementNameLabel->setAlignment(Qt::AlignCenter);
    elementNameLabel->setWordWrap(true);

    elementdisplayLay->setAlignment(Qt::AlignHCenter);
    elementdisplayLay->addWidget(elementIconLabel);
    elementdisplayLay->addWidget(elementNameLabel);
    elementdisplayLay->addStretch();

    elementDispalyWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    return elementDispalyWidget;
}

void ElementsListWidget::setElementsPerRow(int numberOfelementsPerRow)
{
    if (numberOfelementsPerRow > 0) {
        elementsPerRow = numberOfelementsPerRow;
    }
}



void ElementsListWidget::serachElement(const QString& searchText)
{
    clearModel();

    // Iterate through the stored widgets in elementWidgetModel
    for (AbstractElement* element : elementsModel) {
        if (element && element->getName().contains(searchText, Qt::CaseInsensitive)) {
            showWidgetOnView(createDisplayUnit(element));
        }
    }

}

void ElementsListWidget::showWidgetOnView(QWidget* elementDisplayUnit)
{
    if (elementDisplayUnit == nullptr) {
        return;
    }

    QStandardItem* item = new QStandardItem;
    
    // Calculate the row and column count for the new element
    int row = totalModelElements / elementsPerRow;
    int column = totalModelElements % elementsPerRow;

    sourceModel->setItem(row, column, item);

    elementsListLayout->setIndexWidget(item->index(), elementDisplayUnit);

    totalModelElements++;
 }

void ElementsListWidget::clearModel() {
    sourceModel->clear();
    totalModelElements = 0;
 }