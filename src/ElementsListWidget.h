#ifndef ELEMENTSLISTWIDGET_H
#define ELEMENTSLISTWIDGET_H

#include <QWidget>

class QLabel;
class QGridLayout;
class QScrollArea;
class QAbstractScrollArea;
class AbstractElement;

class ElementsListWidget : public QWidget {
    Q_OBJECT
public:
    ElementsListWidget(QWidget* parent = nullptr);

public:
    void addElement(AbstractElement* element);
    void setElementsPerRow(int numberOfelementsPerRow);

private:
    QGridLayout* elementsListLayout;
    int elementsPerRow;
};

#endif // ELEMENTSLISTWIDGET_H
