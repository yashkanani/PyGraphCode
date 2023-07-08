#include "ForLoopElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include "ElementUserInputs.h"

namespace key {
const std::string comboSelectionString = "comboSelection";
const std::string variableContainer = "variableContainer";
const std::string startContainer = "startContainer";
const std::string incrementContainer = "incrementContainer";
const std::string bodyContainer = "bodyContainer";
const std::string endContainer = "endContainer";
}

ForLoopElement::ForLoopElement()
{
    name = "For Loop";
    image = QPixmap(":/resource/For_loop.png");
    type = BasicElementType::FOR_LOOP;

    comboSelection = "Static";

    variableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    startContainer = std::make_shared<BuilderContainer>(nullptr, true);
    incrementContainer = std::make_shared<BuilderContainer>(nullptr, true);
    bodyContainer = std::make_shared<BuilderContainer>(nullptr, true);
    endContainer = std::make_shared<BuilderContainer>(nullptr, true);
}

void ForLoopElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        comboSelection = userInput->getString(key::comboSelectionString);
        variableContainer = userInput->getContainer(key::variableContainer);
        startContainer = userInput->getContainer(key::startContainer);
        incrementContainer = userInput->getContainer(key::incrementContainer);
        bodyContainer = userInput->getContainer(key::bodyContainer);
        endContainer = userInput->getContainer(key::endContainer);
    }
}
std::shared_ptr<ElementUserInputs> ForLoopElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addString(key::comboSelectionString, comboSelection);
    ret->addContainer(key::variableContainer, variableContainer);
    ret->addContainer(key::startContainer, startContainer);
    ret->addContainer(key::incrementContainer, incrementContainer);
    ret->addContainer(key::bodyContainer, bodyContainer);
    ret->addContainer(key::endContainer, endContainer);
    return ret;
}

std::shared_ptr<AbstractElement> ForLoopElement::clone() const
{
    auto ret = std::make_shared<ForLoopElement>();

    // Copy endCondition
    ret->comboSelection = comboSelection;

    // Copy variableContainer
    ret->variableContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->variableContainer->appendContainerInformationList(variableContainer->getContainerInformation());

    // Copy startContainer
    ret->startContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->startContainer->appendContainerInformationList(startContainer->getContainerInformation());

    // Copy incrementContainer
    ret->incrementContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->incrementContainer->appendContainerInformationList(incrementContainer->getContainerInformation());

    // Copy bodyContainer
    ret->bodyContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->bodyContainer->appendContainerInformationList(bodyContainer->getContainerInformation());

    // Copy endContainer
    ret->endContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->endContainer->appendContainerInformationList(endContainer->getContainerInformation());

    return ret;
}

std::shared_ptr<CodeText> ForLoopElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);

    if (variableContainer && endContainer) {

        if (comboSelection.compare("Static") == 0) {
            ret->addToBody("for " + variableContainer->getText(0)->getResult() + QString(" in range(%1):").arg(endContainer->getText(0)->getResult()));
            ret->addToBody("\n");
        } else if (comboSelection.compare("Dynamic") == 0) {
            if (startContainer) {
                ret->addToBody("for " + variableContainer->getText(0)->getResult() + QString(" in range(%1, %2):").arg(startContainer->getText(0)->getResult()).arg(endContainer->getText(0)->getResult()));
                ret->addToBody("\n");
            }
        } else {
            if (startContainer && incrementContainer) {
                ret->addToBody("for " + variableContainer->getText(0)->getResult() + QString(" in range(%1, %2, %3):").arg(startContainer->getText(0)->getResult()).arg(endContainer->getText(0)->getResult()).arg(incrementContainer->getText(0)->getResult()));
                ret->addToBody("\n");
            }
        }
    }

    if (bodyContainer) {
        ret->increaseIndentOfBody();
        ret->append(*(bodyContainer->getText(ret->getCurrentIndentOfBody())));
        ret->removeIndentOfBody();
    }

    return ret;
}

QWidget* ForLoopElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("For Loop", parent);
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

    QGroupBox* variableGroup = new QGroupBox("", wdg);
    QVBoxLayout* variableLay = new QVBoxLayout(variableGroup);

    QList<BasicElementType> acceptedTypes = { BasicElementType::CONSTANT_DECIMAL, BasicElementType::READ_VARIABLE };
    bool subContainer = true;
    if (variableContainer) {
        startContainer->setAcceptedTypes(acceptedTypes);
        QObject::connect(variableContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        variableLay->addWidget(variableContainer.get());
    }

    wdgLayout->addWidget(variableGroup, 0, 0);

    QGroupBox* endGroup = new QGroupBox("", wdg);
    QHBoxLayout* endVariableLay = new QHBoxLayout(endGroup);

    QComboBox* endCondition = new QComboBox();
    endCondition->addItem("Static");
    endCondition->addItem("Dynamic");
    endCondition->addItem("yash");

    endCondition->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    endVariableLay->addWidget(endCondition, Qt::AlignLeft | Qt::AlignTop);

    if (startContainer) {
        startContainer->setAcceptedTypes(acceptedTypes);
        startContainer->setMaxElements(1);
        QObject::connect(startContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        endVariableLay->addWidget(startContainer.get());
        startContainer->hide();
    }

    if (endContainer) {
        endContainer->setAcceptedTypes(acceptedTypes);
        endContainer->setMaxElements(1);
        QObject::connect(endContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        endVariableLay->addWidget(endContainer.get());
        endContainer->show();
    }

    if (incrementContainer) {
        incrementContainer->setAcceptedTypes(acceptedTypes);
        incrementContainer->setMaxElements(1);
        QObject::connect(incrementContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        endVariableLay->addWidget(incrementContainer.get());
        incrementContainer->hide();
    }

    wdgLayout->addWidget(endGroup, 0, 1);

    if (bodyContainer) {
        QObject::connect(bodyContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        wdgLayout->addWidget(bodyContainer.get(), 1, 0, 1, 2);
    }

    // Connect the combo box signals to slots or functions
    QObject::connect(endCondition, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (!startContainer || !endContainer || !incrementContainer) {
            return;
        }

        switch (index) {

        case 0: {
            startContainer->hide();
            endContainer->show();
            incrementContainer->hide();
        } break;
        case 1: {
            startContainer->show();
            endContainer->show();
            incrementContainer->hide();
        } break;
        case 2: {
            startContainer->show();
            endContainer->show();
            incrementContainer->show();
        } break;

        default:
            endContainer->show();
            break;
        }

        comboSelection = endCondition->currentText();
        emit childValueChanged();
    });

    endCondition->setCurrentText(comboSelection);

    return wdg;
}
