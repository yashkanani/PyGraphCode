#include "VariableElement.h"

VariableElement::VariableElement()
{
    name = "Variable";
}

QString VariableElement::getName() const
{
    return name;
}

QImage VariableElement::getImage() const
{
    return image;
}