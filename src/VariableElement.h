#ifndef VARIABLE_ELEMENT_H
#define VARIABLE_ELEMENT_H

#include "AbstractElement.h"

class VariableElement : public AbstractElement {
public:
    VariableElement();

    QString getName() const override;
    QImage getImage() const override;

private:
    QString name;
    QImage image;
};

#endif // VARIABLE_ELEMENT_H