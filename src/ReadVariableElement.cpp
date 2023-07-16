#include "ReadVariableElement.h"
#include "CodeText.h"
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlayout.h>

#include <qwidget.h>

#include "ElementUserInputs.h"
#include <qpushbutton.h>

namespace key {
const std::string variableName = "value";
}

ReadVariableElement::ReadVariableElement()
{
    name = "Read Variable";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::READ_VARIABLE;
}
void ReadVariableElement::updateParameterWidgets(ParameterUIBuilder* const parameterUIBuilder)
{
}
void ReadVariableElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        name = userInput->getString(key::variableName);
    }
}
std::shared_ptr<ElementUserInputs> ReadVariableElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addString(key::variableName, name);
    return ret;
}
std::shared_ptr<AbstractElement> ReadVariableElement::clone() const
{
    auto ret = std::make_shared<ReadVariableElement>();
    ret->setName(this->name);
    return ret;
}

std::shared_ptr<CodeText> ReadVariableElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    ret->addToBody(getName());
    return ret;
}

QWidget* ReadVariableElement::getViewWidget(QWidget* parent)
{

    QGroupBox* wdg = new QGroupBox("Read", parent);
    wdg->setObjectName("ReadVariableGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#ReadVariableGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ReadVariableGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");
    QVBoxLayout* wdgLayout = new QVBoxLayout(wdg);
    wdgLayout->setContentsMargins(1, 1, 1, 1);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel* displayLabel = new QLabel(getName(), wdg);
    displayLabel->setObjectName("readVariableNameText");
    displayLabel->setStyleSheet(
        "QLabel#readVariableNameText{"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "}");
    displayLabel->setAlignment(Qt::AlignCenter); // Align the label's text to the center
    wdgLayout->addWidget(displayLabel);

    return wdg;
}
