#include "OperationElement.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <qcombobox.h>

#include "VariableElement.h"

OperationElement::OperationElement()
{
    name = "Operation";
    image = QPixmap(":/resource/Operation.png");
}

QString OperationElement::getName() const
{
    return name;
}

QPixmap OperationElement::getImage() const
{
    return image;
}

QString OperationElement::getText() const
{
    return "Operation Element: " + name;
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

    VariableElement* firstVariableElement = new VariableElement();
    QWidget* firstVariableWidget = firstVariableElement->getViewWidget(wdg);
    wdgLay->addWidget(firstVariableWidget, 0, 0);

    QComboBox* conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Add to (+)");
    conditionComboBox->addItem("is subtract from (-)");
    conditionComboBox->addItem("is multiply by (x)");
    conditionComboBox->addItem("is divide by (/)");
    conditionComboBox->addItem("is XOR (^)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);

    VariableElement* secondVariableElement = new VariableElement();
    QWidget* secondVariableWidget = secondVariableElement->getViewWidget(wdg);
    wdgLay->addWidget(secondVariableWidget, 0, 2);

    // Connect the combo box signals to slots or functions
    // Example: Connect the currentIndexChanged signal of conditionComboBox
    // to a slot or function that handles the selection change.
    // QObject::connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OperationElement::handleConditionIndexChanged);

    return wdg;
}