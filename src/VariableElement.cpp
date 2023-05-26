#include "VariableElement.h"

VariableElement::VariableElement()
{
    name = "Variable";
    image = QPixmap(":/resource/Variable.png");
}

QString VariableElement::getName() const
{
    return name;
}

QPixmap VariableElement::getImage() const
{
    return image;
}

QString VariableElement::getText() const
{
    return "Variable Element: " + name;
}