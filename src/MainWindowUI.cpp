#include "MainWindowUI.h"
#include "MainWindow.h"

#include "BuilderContainer.h"
#include "ElementDragEventHandler.h"
#include "ElementManager.h"
#include "ElementsCreator.h"
#include "ResultedTextView.h"
#include "BuilderControlsButtons.h"

#include <iostream>
#include <qcombobox.h>
#include <qdrag.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmimedata.h>
#include <qpushbutton.h>
#include <qquickitem.h>
#include <qquickview.h>
#include <qquickwidget.h>
#include <qscrollarea.h>

MainWindowUI::MainWindowUI(MainAppWindow* main)
    : d_mainWindow(main)
{
    createCentralWidget();
}
MainWindowUI::~MainWindowUI()
{
}

void MainWindowUI::createCentralWidget()
{
    QWidget* centralWidget = new QWidget(d_mainWindow);
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    d_mainWindow->setCentralWidget(centralWidget);

    //centralLayout->addWidget(GetApplyStyleButton(),		0, 0);
    //centralLayout->addWidget(GetMainTabWidget(), 1, 0);
    centralLayout->addWidget(getElementsWidget(centralWidget), 0, 0, 4, 1);

    QScrollArea* scrollBuilderArea = new QScrollArea(centralWidget);
    scrollBuilderArea->setWidgetResizable(true); // Allow the scroll area to resize the widget
    BuilderContainer* builderContainer = new BuilderContainer(scrollBuilderArea);
    QObject::connect(builderContainer, &BuilderContainer::EnsureVisible, scrollBuilderArea, &QScrollArea::ensureVisible);
    scrollBuilderArea->setWidget(builderContainer);

    centralLayout->addWidget(getButtonWidget(centralWidget, builderContainer), 0, 1);
    centralLayout->addWidget(scrollBuilderArea, 1, 1, 3, 1);

    centralLayout->addWidget(getElementsCreatorWidget(centralWidget), 0, 2, 2, 1);
    centralLayout->addWidget(getResultedTextViewWidget(centralWidget, builderContainer), 2, 2, 2, 1);

    // Set the column stretch to distribute remaining space
    centralLayout->setRowStretch(1, 1);
    centralLayout->setRowStretch(2, 2);
    centralLayout->setColumnStretch(1, 2);
    centralLayout->setColumnStretch(2, 1);
}

QWidget* MainWindowUI::getElementsWidget(QWidget* parent)
{
    QWidget* elementHolder = new QWidget(parent);
    QVBoxLayout* elementLayout = new QVBoxLayout(elementHolder);

    // Create the main widget to hold the search bar
    QWidget* searchBarWidget = new QWidget(parent);

    // Create a layout for the search bar
    QHBoxLayout* searchBarlayout = new QHBoxLayout(searchBarWidget);
    searchBarlayout->setContentsMargins(0, 0, 0, 0);
    searchBarlayout->setSpacing(5);

    // Create the search icon label
    QLabel* searchIconLabel = new QLabel(searchBarWidget);
    QPixmap searchIconPixmap(":/resource/search.png"); // Replace with the path to your search icon
    searchIconLabel->setPixmap(searchIconPixmap.scaled(16, 16)); // Adjust the size as needed

    // Create the line edit for entering the search text
    QLineEdit* searchLineEdit = new QLineEdit(searchBarWidget);
    searchLineEdit->setPlaceholderText("Search");

    // serach create Button.
    QPushButton* searchClearButton = new QPushButton(searchBarWidget);

    // Add the search icon and line edit to the layout
    searchBarlayout->addWidget(searchIconLabel);
    searchBarlayout->addWidget(searchLineEdit);
    searchBarlayout->addWidget(searchClearButton);

    // Set the layout as the main layout for the search bar widget
    searchBarWidget->setLayout(searchBarlayout);

    // Create the filter combo box
    QComboBox* filterComboBox = new QComboBox(searchBarWidget);
    filterComboBox->addItem("Filter 1");
    filterComboBox->addItem("Filter 2");
    filterComboBox->addItem("Filter 3");

    QWidget* elementsListHolder = new QWidget(searchBarWidget);
    QGridLayout* elementsListLayout = new QGridLayout(elementsListHolder);
    elementsListLayout->setContentsMargins(10, 10, 10, 10);
    elementsListLayout->setSpacing(10);

    QScrollArea* elementsListArea = new QScrollArea(searchBarWidget);
    elementsListArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    elementsListArea->setWidgetResizable(true);
    elementsListArea->setWidget(elementsListHolder);

    // Get all elements from the ElementManager
    ElementManager& elementManager = ElementManager::getInstance();
    std::vector<AbstractElement*> allElements = elementManager.getAllElements();

    // Iterate through all elements and create draggable icons in the grid layout
    int columnCount = 0;
    int rowCount = 0;
    for (AbstractElement* element : allElements) {

        QLabel* elementIconLabel = new QLabel(searchBarWidget);

        elementIconLabel->setAlignment(Qt::AlignCenter);
        elementIconLabel->setStyleSheet("QLabel:hover { background-color: lightgray; }");
        elementIconLabel->setProperty("element", QVariant::fromValue(static_cast<AbstractElement*>(element)));
        elementIconLabel->setCursor(Qt::OpenHandCursor);
        elementIconLabel->setAlignment(Qt::AlignCenter);
        elementIconLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        elementIconLabel->installEventFilter(new ElementDragEventHandler(elementIconLabel)); // Install event filter
        elementIconLabel->setPixmap(element->getImage().scaled(50, 50));

        // Add the element icon label to the grid layout at the appropriate position
        elementsListLayout->addWidget(elementIconLabel, rowCount, columnCount);

        // Increment the column count and move to the next row if necessary
        columnCount++;
        if (columnCount >= 3) {
            columnCount = 0;
            rowCount++;
        }
    }

    elementsListLayout->setRowStretch(elementsListLayout->rowCount(), 1);

    elementLayout->addWidget(searchBarWidget);
    elementLayout->addWidget(filterComboBox);
    elementLayout->addWidget(elementsListArea);

    return elementHolder;
}

QWidget* MainWindowUI::getResultedTextViewWidget(QWidget* parent, BuilderContainer* builderContainer)
{
    ResultedTextView* resultedTextView = new ResultedTextView(parent, builderContainer);
    return resultedTextView;
}

QWidget* MainWindowUI::getElementsCreatorWidget(QWidget* parent)
{
    ElementsCreator* elementsCreator = new ElementsCreator(parent);
    return elementsCreator;
}

QWidget* MainWindowUI::getButtonWidget(QWidget* parent, BuilderContainer* builderContainer)
{
    BuilderControlsButtons* controlButtons = new BuilderControlsButtons(builderContainer, parent);
    return controlButtons;
}
void MainWindowUI::onSearchTextChanged(const QString& searchText)
{
    qDebug() << "change text " << searchText;
    // Handle the signal here
    // You can perform any required actions based on the searchText received from QML
}
