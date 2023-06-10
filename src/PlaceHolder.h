#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <QWidget>

class BuilderContainer;
class PlaceHolder : public QWidget {
public:
    PlaceHolder(QWidget* parent, BuilderContainer* container);
    BuilderContainer* getContainer();
    QString getComboBoxText();

private:
    BuilderContainer* container;
    void createWidgets();
};

#endif // PLACEHOLDER_H