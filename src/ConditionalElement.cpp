#include "ConditionalElement.h"
#include "BuilderContainer.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

#include "BuilderContainer.h"
#include "CodeText.h"
#include "ParameterUIBuilder.h"
#include "ElementUserInputs.h"

namespace key {
const std::string comboSelectionString = "comboSelection";
const std::string firstContainer = "firstContainer";
const std::string secondContainer = "selectionContainer";
}

ConditionalElement::ConditionalElement()
{
    name = "Condition";
    image = QPixmap(":/resource/Conditional.png");
    type = BasicElementType::CONDITIONS;

    firstVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    secondVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    comboSelection = "is Greater than (>)";
}

void ConditionalElement::updateParameterWidgets(ParameterUIBuilder* const parameterUIBuilder)
{
    if (firstVariableContainer) {
        firstVariableContainer->updateParameterWidgets(parameterUIBuilder);
    }
    if (secondVariableContainer) {
        secondVariableContainer->updateParameterWidgets(parameterUIBuilder);
    }
}

void ConditionalElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        comboSelection = userInput->getString(key::comboSelectionString);
        firstVariableContainer = userInput->getContainer(key::firstContainer);
        secondVariableContainer = userInput->getContainer(key::secondContainer);
    }
}
std::shared_ptr<ElementUserInputs> ConditionalElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addString(key::comboSelectionString, comboSelection);
    ret->addContainer(key::firstContainer, firstVariableContainer);
    ret->addContainer(key::secondContainer, secondVariableContainer);
    return ret;
}
std::shared_ptr<AbstractElement> ConditionalElement::clone() const
{
    auto ret = std::make_shared<ConditionalElement>();

    ret->comboSelection = comboSelection;

    ret->firstVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->firstVariableContainer->appendContainerInformationList(firstVariableContainer->getContainerInformation());

    ret->secondVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->secondVariableContainer->appendContainerInformationList(secondVariableContainer->getContainerInformation());

    return ret;
}

std::shared_ptr<CodeText> ConditionalElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    QString line;
    line += "(";
    if (firstVariableContainer) {
        line += firstVariableContainer->getText(0)->getResult();
    }

    if (comboSelection.compare("is Greater than (>)") == 0) {
        line += " > ";

    } else if (comboSelection.compare("is Less than (<)") == 0) {
        line += " < ";

    } else if (comboSelection.compare("is Greater than or equal to (>=)") == 0) {
        line += " >= ";

    } else if (comboSelection.compare("is Less than or equal to (<=)") == 0) {
        line += " <= ";

    } else if (comboSelection.compare("is same as (==)") == 0) {
        line += " == ";

    } else if (comboSelection.compare("is not same as (!=)") == 0) {
        line += " != ";
    }

    if (secondVariableContainer) {
        line += secondVariableContainer->getText(0)->getResult();
    }

    line += ")";

    ret->addToBody(line);
    return ret;
}

QWidget* ConditionalElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("Condition", parent);
    wdg->setObjectName("ConditionalGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#ConditionalGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ConditionalGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QGridLayout* wdgLay = new QGridLayout(wdg);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Set the accepted types for the BuilderContainer
    QList<BasicElementType> acceptedTypes = { BasicElementType::READ_VARIABLE, BasicElementType::CONDITIONS };

    if (firstVariableContainer) {
        firstVariableContainer->setAcceptedTypes(acceptedTypes);
        firstVariableContainer->setMaxElements(1);
        QObject::connect(firstVariableContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        QObject::connect(firstVariableContainer.get(), &BuilderContainer::notifyToParameterWidgets, this, &AbstractElement::notifyToParameterWidgets);
        wdgLay->addWidget(firstVariableContainer.get(), 0, 0);
    }

    QComboBox* conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Greater than (>)");
    conditionComboBox->addItem("is Less than (<)");
    conditionComboBox->addItem("is Greater than or equal to (>=)");
    conditionComboBox->addItem("is Less than or equal to (<=)");
    conditionComboBox->addItem("is same as (==)");
    conditionComboBox->addItem("is not same as (!=)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Connect the combo box signals to notifier.
    QObject::connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=]() {
        comboSelection = conditionComboBox->currentText();
        emit childValueChanged();
    });

    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);
    conditionComboBox->setCurrentText(comboSelection);

    if (secondVariableContainer) {
        secondVariableContainer->setAcceptedTypes(acceptedTypes);
        secondVariableContainer->setMaxElements(1);
        QObject::connect(secondVariableContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        QObject::connect(secondVariableContainer.get(), &BuilderContainer::notifyToParameterWidgets, this, &AbstractElement::notifyToParameterWidgets);
        wdgLay->addWidget(secondVariableContainer.get(), 0, 2);
    }

    return wdg;
}
