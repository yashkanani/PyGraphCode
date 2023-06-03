#include "ConditionalElement.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include "PlaceHolder.h"
#include "BuilderContainer.h"
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qcombobox.h>


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

QString ConditionalElement::getText() const
{
    return "Conditional Element: " + name;
}

QWidget* ConditionalElement::getViewWidget()
{
    QGroupBox* wdg = new QGroupBox("Conditional Element");
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

    QGroupBox* firstGroupBox = new QGroupBox("First Variable", wdg);
    QVBoxLayout* firstLay = new QVBoxLayout(firstGroupBox);

    QComboBox* firstComboBox = new QComboBox(wdg);
    firstComboBox->addItem("Static");
    firstComboBox->addItem("Dynamic");
    firstComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    firstLay->addWidget(firstComboBox);

    QLineEdit* firstLineEdit = new QLineEdit(wdg);
    firstLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    firstLay->addWidget(firstLineEdit);

    bool subContainer = true;
    BuilderContainer* firstContainer = new BuilderContainer(wdg, subContainer);
    firstContainer->hide(); // Initially hide the builder container
    firstLay->addWidget(firstContainer);

    wdgLay->addWidget(firstGroupBox, 0, 0);

    QComboBox* conditionComboBox = new QComboBox(wdg);
    conditionComboBox->addItem("is Greater than (>)");
    conditionComboBox->addItem("is Less than (<)");
    conditionComboBox->addItem("is Greater than or equal to (>=)");
    conditionComboBox->addItem("is Less than or equal to (<=)");
    conditionComboBox->addItem("same as (==)");
    conditionComboBox->addItem("is not same as (!=)");
    conditionComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLay->addWidget(conditionComboBox, 0, 1, Qt::AlignCenter);

    QGroupBox* secondGroupBox = new QGroupBox("Second Variable", wdg);
    QVBoxLayout* secondLay = new QVBoxLayout(secondGroupBox);

    QComboBox* secondComboBox = new QComboBox(wdg);
    secondComboBox->addItem("Static");
    secondComboBox->addItem("Dynamic");
    secondComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    secondLay->addWidget(secondComboBox);

    QLineEdit* secondLineEdit = new QLineEdit(wdg);
    secondLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    secondLay->addWidget(secondLineEdit);

    BuilderContainer* secondContainer = new BuilderContainer(wdg, subContainer);
    secondContainer->hide(); // Initially hide the builder container
    secondLay->addWidget(secondContainer);

    wdgLay->addWidget(secondGroupBox, 0, 2);

    // Connect the combo box signals to slots or functions
    QObject::connect(firstComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the line edit for entering static value
            firstContainer->hide();
            firstLineEdit->show();
        } else {
            // Show the builder container for entering dynamic value
            firstContainer->show();
            firstLineEdit->hide();
        }
    });

    QObject::connect(secondComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Show the line edit for entering static value
            secondContainer->hide();
            secondLineEdit->show();
        } else {
            // Show the builder container for entering dynamic value
            secondContainer->show();
            secondLineEdit->hide();
        }
    });

    return wdg;
}