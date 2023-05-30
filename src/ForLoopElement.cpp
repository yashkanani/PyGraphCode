#include "ForLoopElement.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"
#include <qlabel.h>
#include <qgroupbox.h>

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

QWidget* ForLoopElement::getViewWidget()
{
    QGroupBox* wdg = new QGroupBox("For Loop");
    QGridLayout* wdgLay = new QGridLayout(wdg);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel* forLabel = new QLabel("for", wdg);
    forLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    wdgLay->addWidget(forLabel, 0, 0);

    QComboBox* startComboBox = new QComboBox(wdg);
    startComboBox->addItem("Static");
    startComboBox->addItem("Dynamic");
    wdgLay->addWidget(startComboBox, 0, 1);

    BuilderContainer* startContainer = new BuilderContainer(wdg);
    wdgLay->addWidget(startContainer, 0, 2);

    QLabel* inLabel = new QLabel("in", wdg);
    inLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    wdgLay->addWidget(inLabel, 0, 3);

    QComboBox* inComboBox = new QComboBox(wdg);
    inComboBox->addItem("Static");
    inComboBox->addItem("Dynamic");
    wdgLay->addWidget(inComboBox, 0, 4);

    BuilderContainer* inContainer = new BuilderContainer(wdg);
    wdgLay->addWidget(inContainer, 0, 5);

    QLabel* bodyLabel = new QLabel("body", wdg);
    bodyLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    wdgLay->addWidget(bodyLabel, 1, 0);

    QComboBox* bodyComboBox = new QComboBox(wdg);
    bodyComboBox->addItem("Static");
    bodyComboBox->addItem("Dynamic");
    wdgLay->addWidget(bodyComboBox, 1, 1);

    BuilderContainer* bodyContainer = new BuilderContainer(wdg);
    wdgLay->addWidget(bodyContainer, 1, 2, 1, 4);

    // Connect the combo box signals to slots or functions
    QObject::connect(startComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the widget for entering static value
            startContainer->show();
        } else {
            // Show the builder container for entering dynamic value
            startContainer->hide();
        }
    });

    QObject::connect(inComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the widget for entering static value
            inContainer->show();
        } else {
            // Show the builder container for entering dynamic value
            inContainer->hide();
        }
    });

    QObject::connect(bodyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the widget for entering static value
            bodyContainer->show();
        } else {
            // Show the builder container for entering dynamic value
            bodyContainer->hide();
        }
    });

    // Hide the BuilderContainer by default
    startContainer->show();
    inContainer->show();
    bodyContainer->show();

    return wdg;
}
