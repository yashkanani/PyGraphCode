#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H

#include <QImage>
#include <QString>

class AbstractElement {
public:
    virtual ~AbstractElement() { } // Virtual destructor

    virtual QString getName() const = 0;
    virtual QImage getImage() const = 0;
};

#endif // ABSTRACT_ELEMENT_H