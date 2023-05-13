#include <QMainWindow>

class QWidget;
class MainWindowUI;

class MainAppWindow : public QMainWindow {

public:
    explicit MainAppWindow(QWidget* parent = nullptr);
    ~MainAppWindow();

private:
    std::unique_ptr<MainWindowUI> mainUI;
};