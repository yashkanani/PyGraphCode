#include "WriteVariableElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include "ElementUserInputs.h"

namespace key {
   const std::string dynamicValueContainer = "value";
}

WriteVariableElement::WriteVariableElement()
{
    name = "Write Variable";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::WRITE_VARIABLE;

    dynamicValueContainer = std::make_shared<BuilderContainer>(nullptr, true);
}
void WriteVariableElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        dynamicValueContainer = userInput->getContainer(key::dynamicValueContainer);
    }
}
std::shared_ptr<ElementUserInputs> WriteVariableElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addContainer(key::dynamicValueContainer, dynamicValueContainer);
    return ret;
}
std::shared_ptr<AbstractElement> WriteVariableElement::clone() const
{
    auto ret = std::make_shared<WriteVariableElement>();
    ret->setName(this->name);

    ret->dynamicValueContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->dynamicValueContainer->appendContainerInformationList(dynamicValueContainer->getContainerInformation());

    return ret;
}

std::shared_ptr<CodeText> WriteVariableElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);

    // Dynamic Value set
    if (dynamicValueContainer) {
        ret->addToBody(getName() + " = " + dynamicValueContainer->getText(0)->getResult());
    }

    return ret;
}

QWidget* WriteVariableElement::getViewWidget(QWidget* parent)
{

    QGroupBox* wdg = new QGroupBox("set " + getName(), parent);
    wdg->setObjectName("VariableGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#VariableGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#VariableGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QVBoxLayout* wdgLayout = new QVBoxLayout(wdg);
    wdgLayout->setContentsMargins(0, 0, 0, 0);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Set the accepted types for the BuilderContainer
    QList<BasicElementType> acceptedTypes = { BasicElementType::WRITE_VARIABLE, BasicElementType::CONDITIONS, BasicElementType::CONSTANT_TEXT, BasicElementType::CONSTANT_DECIMAL };
    dynamicValueContainer->setAcceptedTypes(acceptedTypes);
    dynamicValueContainer->setMaxElements(1);
    QObject::connect(dynamicValueContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    QObject::connect(dynamicValueContainer.get(), &BuilderContainer::updateParameterWidgets, this, &AbstractElement::updateParameterWidgets);
    wdgLayout->addWidget(dynamicValueContainer.get());

    return wdg;
}
