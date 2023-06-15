#include "IfLoopElement.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include "BuilderContainer.h"
#include "CodeText.h"

IfLoopElement::IfLoopElement()
{
    name = "If Loop";
    image = QPixmap(":/resource/If_loop.png");
    type = BasicElementType::IF_LOOP;

    conditionsContainer = nullptr;
    onTrueContainer = nullptr;
    onFalseContainer = nullptr;
}

std::shared_ptr<AbstractElement> IfLoopElement::clone() const
{
    return std::make_shared<IfLoopElement>();
}


std::shared_ptr<CodeText> IfLoopElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    
   

    // Dynamic Value set
    if (conditionsContainer) {
        ret->addToBody( "if " + conditionsContainer->getText(0)->getResult() + " :");
        ret->addToBody("\n");
        ret->increaseIndentOfBody();
    }

    // Dynamic Value set
    if (onTrueContainer) {
        ret->append(*(onTrueContainer->getText(ret->getCurrentIndentOfBody())));
         ret->addToBody("\n");
         ret->removeIndentOfBody();
        
    }

    // Dynamic Value set
    if (onFalseContainer) {
        ret->addToBody("else :");
        ret->addToBody("\n");
        ret->increaseIndentOfBody();
        ret->append(*(onFalseContainer->getText(ret->getCurrentIndentOfBody())));
        ret->removeIndentOfBody();
        ret->addToBody("\n");
    }
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

    conditionsContainer = new BuilderContainer(wdg, true);

    // Set the accepted types for the BuilderContainer
    QList<BasicElementType> acceptedTypes = {BasicElementType::CONDITIONS, BasicElementType::READ_VARIABLE };
    conditionsContainer->setAcceptedTypes(acceptedTypes);
    conditionsContainer->setMaxElements(1);
    QObject::connect(conditionsContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);

    // Add the condition widget to the layout
    wdgLay->addWidget(conditionsContainer, 0, 0, 1, 2);

    QGroupBox* onTrueGroupBox = new QGroupBox("On True", wdg);
    QVBoxLayout* onTrueLay = new QVBoxLayout(onTrueGroupBox);

    onTrueContainer = new BuilderContainer(wdg, true);
    QObject::connect(onTrueContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    onTrueLay->addWidget(onTrueContainer);

    wdgLay->addWidget(onTrueGroupBox, 1, 0);

    QGroupBox* onFalseGroupBox = new QGroupBox("On False", wdg);
   
    QVBoxLayout* onFalseLay = new QVBoxLayout(onFalseGroupBox);

    onFalseContainer = new BuilderContainer(wdg, true);
    QObject::connect(onFalseContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    onFalseLay->addWidget(onFalseContainer);

    wdgLay->addWidget(onFalseGroupBox,1,1);

    return wdg;
}