#include "ConditionalElement.h"
#include "BuilderContainer.h"
#include "PlaceHolder.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

#include "CodeText.h"
#include "BuilderContainer.h"

ConditionalElement::ConditionalElement()
{
    name = "Condition";
    image = QPixmap(":/resource/Conditional.png");
    type = BasicElementType::CONDITIONS;
}

std::shared_ptr<AbstractElement> ConditionalElement::clone() const
{
    return std::make_shared<ConditionalElement>();
}

std::shared_ptr<CodeText> ConditionalElement::getText() const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>();
    QString line;
    line += "(";
    if (firstVariableContainer) {
        line += firstVariableContainer->getText()->getResult();
    }

    if (conditionComboBox) {
        switch (conditionComboBox->currentIndex()) {
        case 0: {
            line += " > ";
            break;
        }
        case 1: {
            line += " < ";
            break;
        }
        case 2: {
            line += " >= ";
            break;
        }
        case 3: {
            line += " <= ";
            break;
        }
        case 4: {
            line += " == ";
            break;
        }
        case 5: {
            line += " != ";
            break;
        }
        default: {
            break;
        }
        };
    }

    if (secondVariableContainer) {
        line += secondVariableContainer->getText()->getResult();
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

    firstVariableContainer = new BuilderContainer(wdg, true);
    firstVariableContainer->setAcceptedTypes(acceptedTypes);
    firstVariableContainer->setMaxElements(1);
    QObject::connect(firstVariableContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLay->addWidget(firstVariableContainer, 0, 0);

    conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Greater than (>)");
    conditionComboBox->addItem("is Less than (<)");
    conditionComboBox->addItem("is Greater than or equal to (>=)");
    conditionComboBox->addItem("is Less than or equal to (<=)");
    conditionComboBox->addItem("is same as (==)");
    conditionComboBox->addItem("is not same as (!=)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Connect the combo box signals to notifier.
    QObject::connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AbstractElement::childValueChanged);
    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);

    secondVariableContainer = new BuilderContainer(wdg, true);

    // Set the accepted types for the BuilderContainer
    secondVariableContainer->setAcceptedTypes(acceptedTypes);
    secondVariableContainer->setMaxElements(1);
    QObject::connect(secondVariableContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLay->addWidget(secondVariableContainer, 0, 2);


    return wdg;
}