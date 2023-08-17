#include "ElementsListWidget.h"
#include "AbstractElement.h"
#include "ElementDragEventHandler.h"
#include <QAbstractScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QVariant>
#include <qscrollbar.h>
#include <qtreeview.h>
#include <qstandarditemmodel.h>
#include "ElementItemDelegate.h"
#include <QSortFilterProxyModel>



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

    model = new QStandardItemModel(this);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setSourceModel(model);
    

    elementsListLayout->setModel(proxyModel);

    connect(this, &ElementsListWidget::serachElement, proxyModel, &QSortFilterProxyModel::setFilterFixedString);

    mainlayout->addWidget(elementsListLayout);
    setLayout(mainlayout);

    elementsPerRow = 3;
    totalElements = 0;
    model->setColumnCount(elementsPerRow);
}

void ElementsListWidget::addElement(AbstractElement* element) {

    QStandardItem* item = new QStandardItem;
    item->setData(element->getName(),Qt::UserRole);
    //item->setData(QVariant::fromValue(static_cast<AbstractElement*>(element)), Qt::UserRole); // Store element data

    // Calculate the row and column count for the new element
    int row = totalElements / elementsPerRow;
    int column = totalElements % elementsPerRow;
    
    model->setItem(row, column, item);
    

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


    
    QModelIndex sourceIndex = model->index(row, column, QModelIndex()); // Replace row and column with the appropriate values
    QModelIndex proxyIndex = proxyModel->mapFromSource(sourceIndex);

    elementsListLayout->setIndexWidget(proxyIndex, elementDispalyWidget);
    proxyModel->setData(proxyIndex, element->getName(), Qt::UserRole);
    
    totalElements++;
    
    
}

void ElementsListWidget::setElementsPerRow(int numberOfelementsPerRow)
{
    if (numberOfelementsPerRow > 0) {
        elementsPerRow = numberOfelementsPerRow;
    }
}
