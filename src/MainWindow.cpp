#include "MainWindow.h"
#include "MainWindowUI.h"

MainAppWindow::MainAppWindow(QWidget* parent)
    : QMainWindow(parent)
    , mainUI(std::make_unique<MainWindowUI>(this))
{
    showMaximized();
}
MainAppWindow::~MainAppWindow()
{
}