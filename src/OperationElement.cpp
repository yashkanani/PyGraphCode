#include "OperationElement.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <qcombobox.h>

#include "BuilderContainer.h"
#include "CodeText.h"
#include "ElementUserInputs.h"

namespace key {
const std::string comboSelectionString = "comboSelection";
const std::string firstContainer = "firstContainer";
const std::string secondContainer = "selectionContainer";
}

OperationElement::OperationElement()
{
    name = "Operation";
    image = QPixmap(":/resource/Operation.png");
    type = BasicElementType::OPERATOR;

    comboSelection = "is Add to (+)";
    secondVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    firstVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
}
void OperationElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        comboSelection = userInput->getString(key::comboSelectionString);
        firstVariableContainer = userInput->getContainer(key::firstContainer);
        secondVariableContainer = userInput->getContainer(key::secondContainer);
    }
}

std::shared_ptr<ElementUserInputs> OperationElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addString(key::comboSelectionString, comboSelection);
    ret->addContainer(key::firstContainer, firstVariableContainer);
    ret->addContainer(key::secondContainer, secondVariableContainer);
    return ret;
}
std::shared_ptr<AbstractElement> OperationElement::clone() const
{
    auto ret = std::make_shared<OperationElement>();

    ret->comboSelection = comboSelection;

    ret->firstVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->firstVariableContainer->appendContainerInformationList(firstVariableContainer->getContainerInformation());

    ret->secondVariableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->secondVariableContainer->appendContainerInformationList(secondVariableContainer->getContainerInformation());

    return ret;
}

std::shared_ptr<CodeText> OperationElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    QString line;
    line += "(";
    if (firstVariableContainer) {
        line += firstVariableContainer->getText(0)->getResult();
    }

    if (comboSelection.compare("is Add to (+)") == 0) {
        line += " + ";
    } else if (comboSelection.compare("is subtract from (-)") == 0) {
        line += " - ";
    } else if (comboSelection.compare("is multiply by (x)") == 0) {
        line += " x ";
    } else if (comboSelection.compare("is divide by (/)") == 0) {
        line += " / ";
    } else if (comboSelection.compare("is XOR (^)") == 0) {
        line += " ^ ";
    } else {
    }

    if (secondVariableContainer) {
        line += secondVariableContainer->getText(0)->getResult();
    }

    line += ")";

    ret->addToBody(line);
    return ret;
}

QWidget* OperationElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("Operation", parent);
    wdg->setObjectName("OperationGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#OperationGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#OperationGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QGridLayout* wdgLay = new QGridLayout(wdg);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Set the accepted types for the BuilderContainer
    QList<BasicElementType> acceptedTypes = { BasicElementType::CONSTANT_DECIMAL, BasicElementType::READ_VARIABLE, BasicElementType::CONDITIONS };

    if (firstVariableContainer) {
        firstVariableContainer->setAcceptedTypes(acceptedTypes);
        firstVariableContainer->setMaxElements(1);
        QObject::connect(firstVariableContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        wdgLay->addWidget(firstVariableContainer.get(), 0, 0);
    }

    QComboBox* conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Add to (+)");
    conditionComboBox->addItem("is subtract from (-)");
    conditionComboBox->addItem("is multiply by (x)");
    conditionComboBox->addItem("is divide by (/)");
    conditionComboBox->addItem("is XOR (^)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);

    QObject::connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        comboSelection = conditionComboBox->currentText();
        emit childValueChanged();
    });

    if (secondVariableContainer) {
        secondVariableContainer->setAcceptedTypes(acceptedTypes);
        secondVariableContainer->setMaxElements(1);
        QObject::connect(secondVariableContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        wdgLay->addWidget(secondVariableContainer.get(), 0, 2);
    }

    conditionComboBox->setCurrentText(comboSelection);
    return wdg;
}