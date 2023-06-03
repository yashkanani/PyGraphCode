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
    wdg->setObjectName("ForLoopGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#ForLoopGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ForLoopGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QGridLayout* wdgLayout = new QGridLayout(wdg);
    wdgLayout->setContentsMargins(0, 0, 0, 0);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QGroupBox* startGroup = new QGroupBox("Take", wdg);
    startGroup->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout* startLay = new QHBoxLayout(startGroup);

    QComboBox* startComboBox = new QComboBox(wdg);
    startComboBox->addItem("Static");
    startComboBox->addItem("Dynamic");
    startComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    startLay->addWidget(startComboBox, Qt::AlignLeft | Qt::AlignTop);

    QLineEdit* startLineEdit = new QLineEdit(wdg);
    startLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum); // Set the size policy
    startLay->addWidget(startLineEdit);

    bool subContainer = true;
    BuilderContainer* startContainer = new BuilderContainer(wdg, subContainer);
    startLay->addWidget(startContainer);

    wdgLayout->addWidget(startGroup, 0, 0);

    QGroupBox* inGroup = new QGroupBox("in", wdg);
    inGroup->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout* inLay = new QHBoxLayout(inGroup);

    QComboBox* inComboBox = new QComboBox(wdg);
    inComboBox->addItem("Static");
    inComboBox->addItem("Dynamic");
    inComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inLay->addWidget(inComboBox, Qt::AlignLeft | Qt::AlignTop);

    QLineEdit* inLineEdit = new QLineEdit(wdg);
    inLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum); // Set the size policy
    inLay->addWidget(inLineEdit);

    BuilderContainer* inContainer = new BuilderContainer(wdg, subContainer);
    inLay->addWidget(inContainer);

    wdgLayout->addWidget(inGroup, 0, 2);

    QGroupBox* bodyGroup = new QGroupBox("body", wdg);
    bodyGroup->setContentsMargins(0, 0, 0, 0);
    bodyGroup->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    QVBoxLayout* bodyLayout = new QVBoxLayout(bodyGroup);

    BuilderContainer* bodyContainer = new BuilderContainer(wdg, subContainer);
    bodyLayout->addWidget(bodyContainer);

    wdgLayout->addWidget(bodyGroup, 1, 0, 1, 3);

    // Connect the combo box signals to slots or functions
    QObject::connect(startComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the widget for entering static value
            startContainer->hide();
            startLineEdit->show();
        } else {
            // Show the builder container for entering dynamic value
            startContainer->show();
            startLineEdit->hide();
        }
    });

    QObject::connect(inComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the widget for entering static value
            inContainer->hide();
            inLineEdit->show();
        } else {
            // Show the builder container for entering dynamic value
            inContainer->show();
            inLineEdit->hide();
        }
    });

    // Hide the BuilderContainer by default
    startContainer->hide();
    inContainer->hide();
    startLineEdit->show();
    inLineEdit->show();

    return wdg;
}
