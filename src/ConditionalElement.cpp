#include "ConditionalElement.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"

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

QWidget* ConditionalElement::getViewWidget()
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
    wdgLay->addWidget(new QPushButton("Conditional Variable"));
    return wdg;
}