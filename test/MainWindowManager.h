// MainWindowManager.h
#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H


class MainAppWindow;
class MainWindowManager {

public:
    static MainWindowManager& getAppManage();
    MainAppWindow* getMainAppWindow(); 
    ~MainWindowManager();

private:
    MainWindowManager();
    
    MainAppWindow* mApp;
};

#endif // MAINWINDOWMANAGER_H
