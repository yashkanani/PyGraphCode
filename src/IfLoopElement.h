#ifndef IF_LOOP_ELEMENT_H
#define IF_LOOP_ELEMENT_H

#include "AbstractElement.h"

class IfLoopElement : public AbstractElement {
public:
    IfLoopElement();

    QString getName() const override;
    QPixmap getImage() const override;

private:
    QString name;
    QPixmap image;
};

#endif // IF_LOOP_ELEMENT_H