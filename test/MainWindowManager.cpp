#include "MainWindow.h"
#include "MainWindowManager.h"

MainWindowManager::MainWindowManager()
{
    mApp = new MainAppWindow();
}

MainWindowManager::~MainWindowManager()
{
    mApp->deleteLater();
}

MainWindowManager& MainWindowManager::getAppManage()
{
    static MainWindowManager instance;
    return instance;
}

MainAppWindow* MainWindowManager::getMainAppWindow()
{
    return mApp; // Return a pointer to the MainAppWindow instance
}
