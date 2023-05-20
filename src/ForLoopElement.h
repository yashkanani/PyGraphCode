#ifndef FOR_LOOP_ELEMENT_H
#define FOR_LOOP_ELEMENT_H

#include "AbstractElement.h"

class ForLoopElement : public AbstractElement {
public:
    ForLoopElement();

    QString getName() const override;
    QImage getImage() const override;

private:
    QString name;
    QImage image;
};

#endif // FOR_LOOP_ELEMENT_H