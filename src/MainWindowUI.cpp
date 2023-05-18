#include "MainWindowUI.h"
#include "MainWindow.h"

#include <iostream>
#include <qgridlayout.h>
#include <qquickitem.h>
#include <qquickview.h>
#include <qquickwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>

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
    centralLayout->addWidget(getElementsWidget(centralWidget), 1, 0);
}

QWidget* createSearchBar(QWidget* parent)
{
    // Create the main widget to hold the search bar
    QWidget* searchBarWidget = new QWidget(parent);

    // Create a layout for the search bar
    QHBoxLayout* layout = new QHBoxLayout(searchBarWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    // Create the search icon label
    QLabel* searchIconLabel = new QLabel(searchBarWidget);
    QPixmap searchIconPixmap(":/resource/search.png"); // Replace with the path to your search icon
    searchIconLabel->setPixmap(searchIconPixmap.scaled(16, 16)); // Adjust the size as needed

    // Create the line edit for entering the search text
    QLineEdit* searchLineEdit = new QLineEdit(searchBarWidget);
    searchLineEdit->setPlaceholderText("Search");

    // Add the search icon and line edit to the layout
    layout->addWidget(searchIconLabel);
    layout->addWidget(searchLineEdit);

    // Set the layout as the main layout for the search bar widget
    searchBarWidget->setLayout(layout);

    return searchBarWidget;
}

QWidget* MainWindowUI::getElementsWidget(QWidget* parent)
{
    QWidget* elementHolder = new QWidget(parent);
    QVBoxLayout* layout = new QVBoxLayout(elementHolder);

    QQuickWidget* searchBarWidget = new QQuickWidget();
    searchBarWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    searchBarWidget->setSource(QUrl("qrc:/qml/SerachBar.qml"));
    searchBarWidget->setFocusPolicy(Qt::StrongFocus);   

    QQuickItem* searchBarRoot = dynamic_cast<QQuickItem*>(searchBarWidget->rootObject());
    if (searchBarRoot) {
        connect(searchBarRoot, SIGNAL(searchTextChanged(QString)), this, SLOT(onSearchTextChanged(QString)));
    }

    // Add the searchBarView to the layout or container widget as needed
    layout->addWidget(searchBarWidget);
    layout->addWidget(new QPushButton("hello"));
    layout->addWidget(createSearchBar(parent));
    layout->addWidget(new QPushButton("hello"));
    // SearchBar
    // Filter
    // Basic Elements --> For loop, if Loop, Oprators, Variable.
    // Prebuilt Funcation.
    // Custom Funcation.

    return elementHolder;
}

void MainWindowUI::onSearchTextChanged(const QString& searchText)
{
    qDebug() << "change text " << searchText;
    // Handle the signal here
    // You can perform any required actions based on the searchText received from QML
}