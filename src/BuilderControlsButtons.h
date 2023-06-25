#ifndef BUILDERCONTROLSBUTTONS_H
#define BUILDERCONTROLSBUTTONS_H

#include <QWidget>

// Forward declaration of BuilderContainer
class BuilderContainer;

class BuilderControlsButtons : public QWidget
{
    Q_OBJECT

public:
    BuilderControlsButtons(const BuilderContainer* builderContainer, QWidget* parent = nullptr);

private slots:
    void handleSaveButtonClicked();
    void handleLoadButtonClicked();

private:
    const BuilderContainer* m_builderContainer;
};

#endif // BUILDERCONTROLSBUTTONS_H
