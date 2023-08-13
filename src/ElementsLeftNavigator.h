#ifndef ELEMENTSLEFTNAVIGATOR_H
#define ELEMENTSLEFTNAVIGATOR_H

#include <QWidget>

// Forward declaration of ParameterUIBuilder (assuming it's defined elsewhere)
class ElementsListWidget;

class ElementsLeftNavigator : public QWidget {
    Q_OBJECT
public:
    ElementsLeftNavigator(ElementsListWidget* builderContainer, QWidget* parent = nullptr);

private:
    ElementsListWidget* m_builderContainer;
  

    QWidget* getElementsWidget(QWidget* parent);
};

#endif // ELEMENTSLEFTNAVIGATOR_H
