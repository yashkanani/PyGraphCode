#include "OperationElement.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <qcombobox.h>

#include "BuilderContainer.h"
#include "CodeText.h"

OperationElement::OperationElement()
{
    name = "Operation";
    image = QPixmap(":/resource/Operation.png");
    type = BasicElementType::OPERATOR;

    secondVariableContainer = nullptr;
    firstVariableContainer = nullptr;
}

 std::shared_ptr<AbstractElement> OperationElement::clone() const
{
     return std::make_shared<OperationElement>();
 }


std::shared_ptr<CodeText> OperationElement::getText(int indentLevel) const
 {
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    QString line;
    line += "(";
    if (firstVariableContainer) {
        line += firstVariableContainer->getText(0)->getResult();
    }

    if (conditionComboBox) {
        switch (conditionComboBox->currentIndex()) {
        case 0: {
            line += " + ";
            break;
        }
        case 1: {
            line += " - ";
            break;
        }
        case 2: {
            line += " x ";
            break;
        }
        case 3: {
            line += " / ";
            break;
        }
        case 4: {
            line += " ^ ";
            break;
        }
        default: {
            break;
        }
        };
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
    QList<BasicElementType> acceptedTypes = { BasicElementType::READ_VARIABLE, BasicElementType::CONDITIONS };

    firstVariableContainer = new BuilderContainer(wdg, true);
    firstVariableContainer->setAcceptedTypes(acceptedTypes);
    firstVariableContainer->setMaxElements(1);
    QObject::connect(firstVariableContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLay->addWidget(firstVariableContainer, 0, 0);

    conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Add to (+)");
    conditionComboBox->addItem("is subtract from (-)");
    conditionComboBox->addItem("is multiply by (x)");
    conditionComboBox->addItem("is divide by (/)");
    conditionComboBox->addItem("is XOR (^)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);

    secondVariableContainer = new BuilderContainer(wdg, true);
    secondVariableContainer->setAcceptedTypes(acceptedTypes);
    secondVariableContainer->setMaxElements(1);
    QObject::connect(secondVariableContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLay->addWidget(secondVariableContainer, 0, 2);

    return wdg;
}