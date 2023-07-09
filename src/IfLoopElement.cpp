#include "IfLoopElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "ElementUserInputs.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

namespace key {
const std::string conditionsContainer = "conditionsContainer";
const std::string onTrueContainer = "onTrueContainer";
const std::string onFalseContainer = "onFalseContainer";
}

IfLoopElement::IfLoopElement()
{
    name = "If Loop";
    image = QPixmap(":/resource/If_loop.png");
    type = BasicElementType::IF_LOOP;

    conditionsContainer = std::make_shared<BuilderContainer>(nullptr, true);
    onTrueContainer = std::make_shared<BuilderContainer>(nullptr, true);
    onFalseContainer = std::make_shared<BuilderContainer>(nullptr, true);
}

void IfLoopElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {

        conditionsContainer = userInput->getContainer(key::conditionsContainer);
        onTrueContainer = userInput->getContainer(key::onTrueContainer);
        onFalseContainer = userInput->getContainer(key::onFalseContainer);
    }
}
std::shared_ptr<ElementUserInputs> IfLoopElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addContainer(key::conditionsContainer, conditionsContainer);
    ret->addContainer(key::onTrueContainer, onTrueContainer);
    ret->addContainer(key::onFalseContainer, onFalseContainer);
    return ret;
}

std::shared_ptr<AbstractElement> IfLoopElement::clone() const
{
    auto ret = std::make_shared<IfLoopElement>();

    ret->conditionsContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->conditionsContainer->appendContainerInformationList(conditionsContainer->getContainerInformation());

    ret->onTrueContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->onTrueContainer->appendContainerInformationList(onTrueContainer->getContainerInformation());

    ret->onFalseContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->onFalseContainer->appendContainerInformationList(onFalseContainer->getContainerInformation());
    return ret;
}

std::shared_ptr<CodeText> IfLoopElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);

    // Dynamic Value set
    if (conditionsContainer) {
        ret->addToBody("if " + conditionsContainer->getText(0)->getResult() + " :");
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

    if (conditionsContainer) {
        // Set the accepted types for the BuilderContainer
        QList<BasicElementType> acceptedTypes = { BasicElementType::CONDITIONS, BasicElementType::READ_VARIABLE };
        conditionsContainer->setAcceptedTypes(acceptedTypes);
        conditionsContainer->setMaxElements(1);
        QObject::connect(conditionsContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        QObject::connect(conditionsContainer.get(), &BuilderContainer::updateParameterWidgets, this, &AbstractElement::updateParameterWidgets);

        // Add the condition widget to the layout
        wdgLay->addWidget(conditionsContainer.get(), 0, 0, 1, 2);
    }

    QGroupBox* onTrueGroupBox = new QGroupBox("On True", wdg);
    QVBoxLayout* onTrueLay = new QVBoxLayout(onTrueGroupBox);

    if (onTrueContainer) {
        QObject::connect(onTrueContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        QObject::connect(onTrueContainer.get(), &BuilderContainer::updateParameterWidgets, this, &AbstractElement::updateParameterWidgets);
        onTrueLay->addWidget(onTrueContainer.get());
    }
    wdgLay->addWidget(onTrueGroupBox, 1, 0);

    QGroupBox* onFalseGroupBox = new QGroupBox("On False", wdg);

    QVBoxLayout* onFalseLay = new QVBoxLayout(onFalseGroupBox);

    if (onFalseContainer) {
        QObject::connect(onFalseContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        QObject::connect(onFalseContainer.get(), &BuilderContainer::updateParameterWidgets, this, &AbstractElement::updateParameterWidgets);
        onFalseLay->addWidget(onFalseContainer.get());
    }

    wdgLay->addWidget(onFalseGroupBox, 1, 1);

    return wdg;
}
