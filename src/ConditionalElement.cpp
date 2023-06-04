#include "ConditionalElement.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qcombobox.h>

#include "VariableElement.h"
#include "CodeText.h"


ConditionalElement::ConditionalElement()
{
    name = "Condition";
    image = QPixmap(":/resource/Conditional.png");
}

QString ConditionalElement::getName() const
{
    return name;
}

QPixmap ConditionalElement::getImage() const
{
    return image;
}

std::shared_ptr<CodeText> ConditionalElement::getText() const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>();
    ret->addToBody("Conditional element code\n");
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

    VariableElement* firstVariableElement = new VariableElement();
    QWidget* firstVariableWidget = firstVariableElement->getViewWidget(wdg);
    wdgLay->addWidget(firstVariableWidget, 0, 0);

    QComboBox* conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Greater than (>)");
    conditionComboBox->addItem("is Less than (<)");
    conditionComboBox->addItem("is Greater than or equal to (>=)");
    conditionComboBox->addItem("is Less than or equal to (<=)");
    conditionComboBox->addItem("is same as (==)");
    conditionComboBox->addItem("is not same as (!=)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);

    VariableElement* secondVariableElement = new VariableElement();
    QWidget* secondVariableWidget = secondVariableElement->getViewWidget(wdg);
    wdgLay->addWidget(secondVariableWidget, 0, 2);

    // Connect the combo box signals to slots or functions
    // Example: Connect the currentIndexChanged signal of conditionComboBox
    // to a slot or function that handles the selection change.
    // QObject::connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ConditionalElement::handleConditionIndexChanged);

    return wdg;
}