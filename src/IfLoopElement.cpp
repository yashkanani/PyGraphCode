#include "IfLoopElement.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"


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

QWidget* IfLoopElement::getViewWidget()
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
    wdgLay->addWidget(new QPushButton("If loop"));
    return wdg;
}
