
#ifndef MainWindowUI_H
#define MainWindowUI_H

#include <qobject.h>

class BuilderContainer;
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
    QWidget* getResultedTextViewWidget(QWidget*, BuilderContainer* builderContainer);
    QWidget* getElementsCreatorWidget(QWidget* parent);

    MainAppWindow* d_mainWindow;
};
#endif