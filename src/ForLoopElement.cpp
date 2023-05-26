#include "ForLoopElement.h"
#include <qpainter.h>

ForLoopElement::ForLoopElement()
{
    name = "For Loop";
    image = QPixmap(":/resource/For_loop.png");
}

QString ForLoopElement::getName() const
{
    return name;
}

QPixmap ForLoopElement::getImage() const
{
    return image;
}

QString ForLoopElement::getText() const
{
    return "For Loop Element: " + name;
}