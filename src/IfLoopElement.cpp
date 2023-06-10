#include "IfLoopElement.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include "ConditionalElement.h"
#include "CodeText.h"

IfLoopElement::IfLoopElement()
{
    name = "If Loop";
    image = QPixmap(":/resource/If_loop.png");
    type = BasicElementType::IF_LOOP;
}

std::shared_ptr<AbstractElement> IfLoopElement::clone() const
{
    return std::make_shared<IfLoopElement>();
}


std::shared_ptr<CodeText> IfLoopElement::getText() const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>();
    ret->addToBody("ifloop element code\n");
    return ret;
}

QWidget* IfLoopElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("If Loop", parent);
    wdg->setObjectName("IfLoopGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#IfLoopGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#IfLoopGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QGridLayout* wdgLay = new QGridLayout(wdg);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Create an instance of the Conditionalelement class
    ConditionalElement conditionElement;

    // Use the getViewWidget function of the Conditionalelement to generate the condition part
    QWidget* conditionWidget = conditionElement.getViewWidget();

    // Add the condition widget to the layout
    wdgLay->addWidget(conditionWidget, 0, 0, 1, 2);

    QGroupBox* onTrueGroupBox = new QGroupBox("On True", wdg);
    QVBoxLayout* onTrueLay = new QVBoxLayout(onTrueGroupBox);

    BuilderContainer* onTrueContainer = new BuilderContainer(wdg, true);
    onTrueLay->addWidget(onTrueContainer);

    wdgLay->addWidget(onTrueGroupBox, 1, 0);

    QGroupBox* onFalseGroupBox = new QGroupBox("On False", wdg);
    QVBoxLayout* onFalseLay = new QVBoxLayout(onFalseGroupBox);

    BuilderContainer* onFalseContainer = new BuilderContainer(wdg, true);
    onFalseLay->addWidget(onFalseContainer);

    wdgLay->addWidget(onFalseGroupBox,1,1);

    return wdg;
}