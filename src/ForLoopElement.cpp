#include "ForLoopElement.h"

ForLoopElement::ForLoopElement()
{
    name = "For Loop";
}

QString ForLoopElement::getName() const
{
    return name;
}

QImage ForLoopElement::getImage() const
{
    return image;
}