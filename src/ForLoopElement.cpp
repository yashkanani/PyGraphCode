#include "ForLoopElement.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"

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

QWidget* ForLoopElement::getViewWidget() {
    QWidget* wdg = new QWidget();
    QGridLayout* wdgLay = new QGridLayout(wdg);
    
   /* startLoop = std::make_shared<PlaceHolder>(wdg, new BuilderContainer(wdg));
    wdgLay->addWidget(startLoop.get(), 0, 0);

    endLoop = std::make_shared<PlaceHolder>(wdg, new BuilderContainer(wdg));
    wdgLay->addWidget(endLoop.get(), 0, 0);

    body = std::make_shared<PlaceHolder>(wdg, new BuilderContainer(wdg));
    wdgLay->addWidget(body.get(), 0, 0);*/

    wdgLay->addWidget(new BuilderContainer(wdg));
    wdgLay->addWidget(new QPushButton("For loop"));
    return wdg;
}
