#include "ConditionalElement.h"

ConditionalElement::ConditionalElement()
{
    name = "Condition";
    image = QPixmap(":/resource/Conditional.png");
}

QString ConditionalElement::getName() const
{
    return name;
}

QPixmap ConditionalElement::getImage() const
{
    return image;
}

QString ConditionalElement::getText() const
{
    return "Conditional Element: " + name;
}