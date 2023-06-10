#include "AbstractElement.h"

AbstractElement::AbstractElement()
{
    name = "";
    type = BasicElementType::UNKNOW;
}

QString AbstractElement::getName() const
{
    return name;
}

BasicElementType AbstractElement::getType() const
{
    return type;
}

QPixmap AbstractElement::getImage() const
{
    return image;
}

void AbstractElement::setName(const QString& elementName)
{
    name = elementName;
}