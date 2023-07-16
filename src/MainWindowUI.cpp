#include "MainWindowUI.h"
#include "MainWindow.h"
#include "ElementManager.h"
#include "ElementsListWidget.h"
#include "BuilderControlPanel.h"

#include <qcombobox.h>
#include <qdebug.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

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

    centralLayout->addWidget(getElementsWidget(centralWidget), 0, 0);
    centralLayout->addWidget(customElementWidget, 1, 0);
    centralLayout->addWidget(new BuilderControlPanel(customElementWidget, centralWidget), 0, 1, 2, 1);
    centralLayout->setColumnStretch(1, 1);
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

void MainWindowUI::onSearchTextChanged(const QString& searchText)
{
    qDebug() << "change text " << searchText;
    // Handle the signal here
    // You can perform any required actions based on the searchText received from QML
}
