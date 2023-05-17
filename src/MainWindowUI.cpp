#include "MainWindowUI.h"
#include "MainWindow.h"

#include <iostream>
#include <qgridlayout.h>
#include <qmenubar.h>
#include <qpushbutton.h>
#include <qtoolbar.h>
#include <qdockwidget.h>
#include <qboxlayout.h>
#include <qlistwidget.h>

MainWindowUI::MainWindowUI(MainAppWindow* main)
    : d_mainWindow(main)
{
    addMenuBar();
    addToolBar();
    addToolBar();
    addCentralWidget();
    addDockWigets();
}
MainWindowUI::~MainWindowUI()
{
}

void MainWindowUI::addCentralWidget()
{
    QWidget* centralWidget = new QWidget(d_mainWindow);
    QGridLayout* centralLayout = new QGridLayout(centralWidget);
    d_mainWindow->setCentralWidget(centralWidget);

    
    //centralLayout->addWidget(GetApplyStyleButton(), 0, 0);
    //centralLayout->addWidget(getMainTabWidget(), 0, 0);
}

void MainWindowUI::addMenuBar()
{
    QMenuBar* menuBar = new QMenuBar(d_mainWindow);
    d_mainWindow->setMenuBar(menuBar);

    // Create File menu
    QMenu* fileMenu = menuBar->addMenu("File");

    // Create File menu actions
    QAction* newAction = new QAction("New", d_mainWindow);
    QAction* openAction = new QAction("Open", d_mainWindow);
    QAction* saveAction = new QAction("Save", d_mainWindow);

    // Add actions to the File menu
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    // Connect actions to slots or functions if needed

    // Create Edit menu
    QMenu* editMenu = menuBar->addMenu("Edit");

    // Create Edit menu actions
    QAction* cutAction = new QAction("Cut", d_mainWindow);
    QAction* copyAction = new QAction("Copy", d_mainWindow);
    QAction* pasteAction = new QAction("Paste", d_mainWindow);

    // Add actions to the Edit menu
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
}
void MainWindowUI::addToolBar()
{
    QToolBar* toolBar = new QToolBar(d_mainWindow);
    d_mainWindow->addToolBar(toolBar);
   
    // Create toolbar actions
    QAction* action1 = new QAction("Action 1", d_mainWindow);
    QAction* action2 = new QAction("Action 2", d_mainWindow);
    QAction* action3 = new QAction("Action 3", d_mainWindow);

    // Add actions to the toolbar
    toolBar->addAction(action1);
    toolBar->addAction(action2);
    toolBar->addAction(action3);

}

void MainWindowUI::addDockWigets()
{
    {
        QDockWidget* wdg = new QDockWidget(d_mainWindow);
        d_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, wdg);

        QWidget* dockWidgetContents = new QWidget();
        QVBoxLayout* lay = new QVBoxLayout(dockWidgetContents);

        lay->addWidget(new QPushButton("hello"));

        QListWidget* listWidget = new QListWidget();
        listWidget->addItem("Item 1");
        listWidget->addItem("Item 2");
        listWidget->addItem("Item 3");

        lay->addWidget(listWidget);
        wdg->setWidget(dockWidgetContents);
    }
   
    {
        QDockWidget* wdg = new QDockWidget(d_mainWindow);
        d_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, wdg);

        QWidget* dockWidgetContents = new QWidget();
        QVBoxLayout* lay = new QVBoxLayout(dockWidgetContents);

        lay->addWidget(new QPushButton("hello"));

        QListWidget* listWidget = new QListWidget();
        listWidget->addItem("Item 4");
        listWidget->addItem("Item 5");
        listWidget->addItem("Item 6");

        lay->addWidget(listWidget);
        wdg->setWidget(dockWidgetContents);
    }
    
}