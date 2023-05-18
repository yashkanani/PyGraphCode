
#ifndef MainWindowUI_H
#define MainWindowUI_H

#include <qobject.h>

class MainAppWindow;
class MainWindowUI : public QObject {
    Q_OBJECT
public:

    explicit MainWindowUI(MainAppWindow* main);
    ~MainWindowUI();


private slots:
    void onSearchTextChanged(const QString& searchText);

private:
    void createCentralWidget();
    QWidget* getElementsWidget(QWidget*);
    

    MainAppWindow* d_mainWindow;
};
#endif