#ifndef ELEMENTSCREATOR_H
#define ELEMENTSCREATOR_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <qgridlayout.h>

class AbstractElement;
class ElementsCreator : public QWidget {
    Q_OBJECT

public:
    explicit ElementsCreator(QWidget* parent = nullptr);
   
private slots:
    void onAddVariableClicked();

private:
    void addElement(std::shared_ptr<AbstractElement> element);
    void addReadVariableElement(const QString& variableName);
    void addWriteVariableElement(const QString& variableName);

    QGridLayout* variableListLayout;
    int columnCount = 0;
    int rowCount = 0;


    std::vector<std::shared_ptr<AbstractElement>> customeReadVariables;
    std::vector<std::shared_ptr<AbstractElement>> customeWriteVariables;
};

#endif // ELEMENTSCREATOR_H