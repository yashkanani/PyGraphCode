#include "ConditionalElement.h"

ConditionalElement::ConditionalElement()
{
    name = "Condition";
}

QString ConditionalElement::getName() const
{
    return name;
}

QImage ConditionalElement::getImage() const
{
    return image;
}