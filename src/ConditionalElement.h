#ifndef CONDITIONAL_ELEMENT_H
#define CONDITIONAL_ELEMENT_H

#include "AbstractElement.h"

class ConditionalElement : public AbstractElement {
public:
    ConditionalElement();

    QString getName() const override;
    QPixmap getImage() const override;

private:
    QString name;
    QPixmap image;
};

#endif // CONDITIONAL_ELEMENT_H