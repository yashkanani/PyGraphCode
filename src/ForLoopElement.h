#ifndef FOR_LOOP_ELEMENT_H
#define FOR_LOOP_ELEMENT_H

#include "AbstractElement.h"

class ForLoopElement : public AbstractElement {
public:
    ForLoopElement();

    QString getName() const override;
    QPixmap getImage() const override;

private:
    QString name;
    QPixmap image;
};

#endif // FOR_LOOP_ELEMENT_H