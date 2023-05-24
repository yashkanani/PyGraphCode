#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H

#include <QPixmap>
#include <QString>
#include <qmetatype.h>

class AbstractElement {
public:
    virtual ~AbstractElement() { } // Virtual destructor

    virtual QString getName() const = 0;
    virtual QPixmap getImage() const = 0;
};
Q_DECLARE_METATYPE(AbstractElement*);
#endif // ABSTRACT_ELEMENT_H