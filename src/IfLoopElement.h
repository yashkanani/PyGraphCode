#ifndef IF_LOOP_ELEMENT_H
#define IF_LOOP_ELEMENT_H

#include "AbstractElement.h"

class IfLoopElement : public AbstractElement {
public:
    IfLoopElement();

    QString getName() const override;
    QImage getImage() const override;

private:
    QString name;
    QImage image;
};

#endif // IF_LOOP_ELEMENT_H