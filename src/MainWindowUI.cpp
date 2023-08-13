#include "MainWindowUI.h"
#include "MainWindow.h"
#include "ElementManager.h"
#include "ElementsListWidget.h"
#include "BuilderControlPanel.h"
#include "ElementsLeftNavigator.h"


#include <qdebug.h>
#include <qgridlayout.h>



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
    centralWidget->setObjectName("centralWidget");

    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    d_mainWindow->setCentralWidget(centralWidget);

    ElementsListWidget* customElementWidget = new ElementsListWidget(centralWidget);
    
    centralLayout->addWidget(new ElementsLeftNavigator(customElementWidget, centralWidget), 0, 0);
    centralLayout->addWidget(new BuilderControlPanel(customElementWidget, centralWidget), 0, 1);

    centralLayout->setColumnStretch(1, 1);
}



void MainWindowUI::onSearchTextChanged(const QString& searchText)
{
    qDebug() << "change text " << searchText;
    // Handle the signal here
    // You can perform any required actions based on the searchText received from QML
}
