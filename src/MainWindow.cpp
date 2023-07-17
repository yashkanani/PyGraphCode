#include "MainWindow.h"
#include "MainWindowUI.h"
#include <qfile.h>
#include <qdebug.h>

MainAppWindow::MainAppWindow(QWidget* parent)
    : QMainWindow(parent)
    , mainUI(std::make_unique<MainWindowUI>(this))
{
    applyStyleSheet();
    showMaximized();
}

void MainAppWindow::applyStyleSheet()
{
    
    QFile styleFile(":stylesheet.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString qssContent = styleFile.readAll();
        setStyleSheet(qssContent);
        styleFile.close();
    } else {
        // Handle file loading error
        qDebug() << "Failed to load stylesheet.qss resource file:" << styleFile.errorString();
    }
}

MainAppWindow::~MainAppWindow()
{
}