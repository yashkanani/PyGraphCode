#ifndef BUILDERCONTROLSBUTTONS_H
#define BUILDERCONTROLSBUTTONS_H

#include <QWidget>

// Forward declaration of BuilderContainer
class BuilderContainer;
class ElementsListWidget;
class BuilderControlsButtons : public QWidget {
    Q_OBJECT

public:
    BuilderControlsButtons(BuilderContainer* builderContainer, ElementsListWidget* customElementWidget, QWidget* parent = nullptr);

private slots:
    void handleSaveButtonClicked();
    void handleLoadButtonClicked();

private:
     BuilderContainer* m_builderContainer;
     ElementsListWidget* m_customElementWidget;
};

#endif // BUILDERCONTROLSBUTTONS_H
