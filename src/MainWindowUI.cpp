#include "MainWindowUI.h"
#include "MainWindow.h"

#include "BuilderContainer.h"
#include "ElementDragEventHandler.h"
#include "ElementManager.h"
#include "ElementsCreator.h"
#include "ResultedTextView.h"
#include "BuilderControlsButtons.h"
#include "ElementsListWidget.h"

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

    

    ElementsListWidget* customElementWidget = new ElementsListWidget(centralWidget);
  

    centralLayout->addWidget(getElementsWidget(centralWidget), 0, 0, 2, 1);
    centralLayout->addWidget(customElementWidget, 2, 0, 2, 1);

    QScrollArea* scrollBuilderArea = new QScrollArea(centralWidget);
    scrollBuilderArea->setWidgetResizable(true); // Allow the scroll area to resize the widget
    BuilderContainer* builderContainer = new BuilderContainer(scrollBuilderArea);
    QObject::connect(builderContainer, &BuilderContainer::EnsureVisible, scrollBuilderArea, &QScrollArea::ensureVisible);
    scrollBuilderArea->setWidget(builderContainer);

    centralLayout->addWidget(getButtonWidget(builderContainer, customElementWidget, centralWidget), 0, 1);
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

    ElementsListWidget* elementsListHolder = new ElementsListWidget(searchBarWidget);

    // Get all elements from the ElementManager
    // Iterate through all elements and create draggable icons in the grid layout
    ElementManager& elementManager = ElementManager::getInstance();
    std::vector<AbstractElement*> allElements = elementManager.getAllElements();
    for (AbstractElement* element : allElements) { 
        elementsListHolder->addElement(element);
    }

    elementLayout->addWidget(searchBarWidget);
    elementLayout->addWidget(filterComboBox);
    elementLayout->addWidget(elementsListHolder);

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

QWidget* MainWindowUI::getButtonWidget(BuilderContainer* builderContainer, ElementsListWidget* customElementWidget, QWidget* parent)
{
    BuilderControlsButtons* controlButtons = new BuilderControlsButtons(builderContainer, customElementWidget, parent); 
    return controlButtons;
}
void MainWindowUI::onSearchTextChanged(const QString& searchText)
{
    qDebug() << "change text " << searchText;
    // Handle the signal here
    // You can perform any required actions based on the searchText received from QML
}
