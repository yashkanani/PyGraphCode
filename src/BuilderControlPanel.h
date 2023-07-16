#ifndef BUILDERCONTROLPANEL_H
#define BUILDERCONTROLPANEL_H

#include <QWidget>
#include <QGridLayout>

class ElementsListWidget;
class BuilderContainer;

class BuilderControlPanel : public QWidget {
    Q_OBJECT
public:
    explicit BuilderControlPanel(ElementsListWidget* customElementWidget, QWidget* parent = nullptr);

private:
    QWidget* getResultedTextViewWidget(QWidget*, BuilderContainer* builderContainer);
    QWidget* getElementsCreatorWidget(QWidget* parent);

    QWidget* getButtonWidget(BuilderContainer* builderContainer, ElementsListWidget* customElementWidget, QWidget* parent);


    QGridLayout* m_layout;
};

#endif // BUILDERCONTROLPANEL_H