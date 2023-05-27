#include "VariableElement.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"

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


QWidget* VariableElement::getViewWidget()
{
    QWidget* wdg = new QWidget();
    QGridLayout* wdgLay = new QGridLayout(wdg);

    /* startLoop = std::make_shared<PlaceHolder>(wdg, new BuilderContainer(wdg));
    wdgLay->addWidget(startLoop.get(), 0, 0);

    endLoop = std::make_shared<PlaceHolder>(wdg, new BuilderContainer(wdg));
    wdgLay->addWidget(endLoop.get(), 0, 0);

    body = std::make_shared<PlaceHolder>(wdg, new BuilderContainer(wdg));
    wdgLay->addWidget(body.get(), 0, 0);*/

    wdgLay->addWidget(new BuilderContainer(wdg));
    wdgLay->addWidget(new QPushButton("Variable"));
    return wdg;
}
