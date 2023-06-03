#include "VariableElement.h"
#include "BuilderContainer.h"
#include "PlaceHolder.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>

VariableElement::VariableElement()
{
    name = "Variable";
    image = QPixmap(":/resource/Variable.png");
}

QString VariableElement::getName() const
{
    return name;
}

QPixmap VariableElement::getImage() const
{
    return image;
}

QString VariableElement::getText() const
{
    return "Variable Element: " + name;
}

QWidget* VariableElement::getViewWidget(QWidget* parent)
{

    QGroupBox* wdg = new QGroupBox("Variable", parent);
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

    QComboBox* comboBox = new QComboBox(wdg);
    comboBox->addItem("Read");
    comboBox->addItem("Static");
    comboBox->addItem("Dynamic");
    comboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLayout->addWidget(comboBox);

    QLineEdit* lineEdit = new QLineEdit(wdg);
    lineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    lineEdit->hide(); // Initially hide the line edit
    wdgLayout->addWidget(lineEdit);

    BuilderContainer* builderContainer = new BuilderContainer(wdg, true);
    builderContainer->hide(); // Initially hide the builder container
    wdgLayout->addWidget(builderContainer);

    // Connect the combo box signal to a lambda function
    QObject::connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 0) {
            // Neither static nor dynamic, hide both line edit and builder container
            lineEdit->hide();
            builderContainer->hide();

        } else if (index == 1) {
            // Show the line edit for entering static value
            lineEdit->show();
            builderContainer->hide();

        } else {
            // Show the builder container for entering dynamic value
            lineEdit->hide();
            builderContainer->show();
        }
    });

    return wdg;
}
