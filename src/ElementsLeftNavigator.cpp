#include "ElementsLeftNavigator.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGridLayout>

#include "ElementsListWidget.h"
#include "ElementManager.h"

#include <qcombobox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qbuttongroup.h>

#include "ImageButton.h"
#include "SearchBarWidget.h"
#include <qstackedwidget.h>


// Include other necessary headers for getElementsCreatorWidget and getResultedTextViewWidget

ElementsLeftNavigator::ElementsLeftNavigator(ElementsListWidget* customElementWidget, QWidget* parent)
    : QWidget(parent)
    , m_customElementWidget(customElementWidget)
{
    
  

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* tabWidget = new QWidget(this);
    tabWidget->setObjectName("elementNavigatorTabwidget");

    QHBoxLayout* tabWidgtLay = new QHBoxLayout(tabWidget);
    tabWidgtLay->setContentsMargins(0, 0, 0, 0);
    tabWidgtLay->setSpacing(0);

    QWidget* tabBar = new QWidget(tabWidget);
    tabBar->setObjectName("elementNavigatorTabwidget_tabBar");

    QVBoxLayout* tabBarLay = new QVBoxLayout(tabBar);
    tabBarLay->setContentsMargins(0, 0, 0, 0);
    
    
    QButtonGroup* buttonGroup = new QButtonGroup(tabBar);

    QStackedWidget* m_stackedWidget = new QStackedWidget(tabWidget);
    m_stackedWidget->setObjectName("elementNavigatorTabwidget_tabDataWidget");

    // Create a first tab.
    QPushButton* prebuiltSelectorButton = new QPushButton(tabBar);
    prebuiltSelectorButton->setCheckable(true);
    prebuiltSelectorButton->setChecked(true);
    prebuiltSelectorButton->setObjectName("elementsLeftNavigator_PrebuiltButton");
    tabBarLay->addWidget(new ImageButton(prebuiltSelectorButton, "Element", "imageButtonText", tabBar));
    m_stackedWidget->addWidget(getElementsWidget(tabWidget));
    buttonGroup->addButton(prebuiltSelectorButton);

    QObject::connect(prebuiltSelectorButton, &QPushButton::toggled, this, [=](bool checked) {
        if (checked) {
            m_stackedWidget->setCurrentIndex(0);
        } 
    });

     // Create a second tab.
    QPushButton* customSelectorButton = new QPushButton(tabBar);
    customSelectorButton->setCheckable(true);
    customSelectorButton->setObjectName("elementsLeftNavigator_customButton");
    tabBarLay->addWidget(new ImageButton(customSelectorButton, "Modules", "imageButtonText", tabBar));
    m_stackedWidget->addWidget(m_customElementWidget);
    buttonGroup->addButton(customSelectorButton);

    QObject::connect(customSelectorButton, &QPushButton::toggled, this, [=](bool checked) { 
        if (checked) {
            m_stackedWidget->setCurrentIndex(1); 
        }
    });

    tabBarLay->addStretch();
    tabWidgtLay->addWidget(tabBar);
    tabWidgtLay->addWidget(m_stackedWidget);
    

    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    
}


QWidget* ElementsLeftNavigator::getElementsWidget(QWidget* parent)
{
    QWidget* elementHolder = new QWidget(parent);
    elementHolder->setObjectName("prebuiltElementsList");

    QVBoxLayout* elementLayout = new QVBoxLayout(elementHolder);
    elementLayout->setContentsMargins(0, 0, 0, 0);
    elementHolder->setProperty("background_transparent", true);

    //// Create the main widget to hold the search bar
    //QWidget* searchBarWidget = new QWidget(parent);

    //// Create a layout for the search bar
    //QHBoxLayout* searchBarlayout = new QHBoxLayout(searchBarWidget);
    //searchBarlayout->setContentsMargins(0, 0, 0, 0);
    //searchBarlayout->setSpacing(5);

    //// Create the search icon label
    //QLabel* searchIconLabel = new QLabel(searchBarWidget);
    //QPixmap searchIconPixmap(":/resource/search.png"); // Replace with the path to your search icon
    //searchIconLabel->setPixmap(searchIconPixmap.scaled(16, 16)); // Adjust the size as needed

    //// Create the line edit for entering the search text
    //QLineEdit* searchLineEdit = new QLineEdit(searchBarWidget);
    //searchLineEdit->setPlaceholderText("Search");

    //// serach create Button.
    //QPushButton* searchClearButton = new QPushButton(searchBarWidget);

    //// Add the search icon and line edit to the layout
    //searchBarlayout->addWidget(searchIconLabel);
    //searchBarlayout->addWidget(searchLineEdit);
    //searchBarlayout->addWidget(searchClearButton);

    //// Set the layout as the main layout for the search bar widget
    //searchBarWidget->setLayout(searchBarlayout);

    SearchBarWidget* searchBarWidget = new SearchBarWidget(elementHolder);

    ElementsListWidget* elementsListHolder = new ElementsListWidget(elementHolder);
    connect(searchBarWidget, &SearchBarWidget::searchTextChanged, elementsListHolder, &ElementsListWidget::serachElement);

    // Get all elements from the ElementManager
    // Iterate through all elements and create draggable icons in the grid layout
    ElementManager& elementManager = ElementManager::getInstance();
    std::vector<AbstractElement*> allElements = elementManager.getAllElements();
    for (AbstractElement* element : allElements) {
        elementsListHolder->addElement(element);
    }

    elementLayout->addWidget(searchBarWidget);
    
    elementLayout->addWidget(elementsListHolder);

    return elementHolder;
}