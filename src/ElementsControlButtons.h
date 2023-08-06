#ifndef ELEMENTSCONTROLBUTTONS_H
#define ELEMENTSCONTROLBUTTONS_H

#include <QWidget>

class QPushButton;

class ElementsControlButtons : public QWidget
{
    Q_OBJECT

public:
    ElementsControlButtons(QWidget* parent = nullptr);

signals:
    void addButtonClicked();

};

#endif // ELEMENTSCONTROLBUTTONS_H
