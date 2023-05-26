#include "IfLoopElement.h"

IfLoopElement::IfLoopElement()
{
    name = "If Loop";
    image = QPixmap(":/resource/If_loop.png");
}

QString IfLoopElement::getName() const
{
    return name;
}

QPixmap IfLoopElement::getImage() const
{
    return image;
}

QString IfLoopElement::getText() const
{
    return "If Loop Element: " + name;
}