#ifndef CONDITIONAL_ELEMENT_H
#define CONDITIONAL_ELEMENT_H

#include "AbstractElement.h"

class ConditionalElement : public AbstractElement {
public:
    ConditionalElement();

    QString getName() const override;
    QImage getImage() const override;

private:
    QString name;
    QImage image;
};

#endif // CONDITIONAL_ELEMENT_H