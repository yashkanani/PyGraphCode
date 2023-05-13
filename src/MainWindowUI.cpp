#include "MainWindow.h"
#include "MainWindowUI.h"

#include<qgridlayout.h>
#include <iostream>


MainWindowUI::MainWindowUI(MainAppWindow* main)
    : d_mainWindow(main)
{
}
MainWindowUI::~MainWindowUI() {

}


void MainWindowUI::createCentralWidget()
{
    QWidget* centralWidget = new QWidget(d_mainWindow);
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    d_mainWindow->setCentralWidget(centralWidget);

    //centralLayout->addWidget(GetApplyStyleButton(),		0, 0);
    //centralLayout->addWidget(GetMainTabWidget(), 1, 0);
}