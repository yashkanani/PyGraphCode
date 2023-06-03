#ifndef VARIABLE_ELEMENT_H
#define VARIABLE_ELEMENT_H

#include "AbstractElement.h"

class VariableElement : public AbstractElement {
public:
    VariableElement();

    QString getName() const override;
    QPixmap getImage() const override;
    QString getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    QString name;
    QPixmap image;
};

#endif // VARIABLE_ELEMENT_H