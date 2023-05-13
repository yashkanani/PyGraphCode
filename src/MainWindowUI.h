#include <qobject.h>

class MainAppWindow;
class MainWindowUI : public QObject {
public:

    explicit MainWindowUI(MainAppWindow* main);
    ~MainWindowUI();

private:
    void createCentralWidget();
    MainAppWindow* d_mainWindow;
};