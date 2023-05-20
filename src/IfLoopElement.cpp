#include "IfLoopElement.h"

IfLoopElement::IfLoopElement()
{
    name = "If Loop";
}

QString IfLoopElement::getName() const
{
    return name;
}

QImage IfLoopElement::getImage() const
{
    return image;
}