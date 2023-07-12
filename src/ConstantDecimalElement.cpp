#include "ConstantDecimalElement.h"
#include "CodeText.h"
#include "ElementUserInputs.h"
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include <qcheckbox.h>
#include "InputLabelDialog.h"

namespace key {
const std::string lineEditValue = "inputText";
}

ConstantDecimalElement::ConstantDecimalElement()
{
    name = "Constant Number";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::CONSTANT_DECIMAL;

    lineEditValue = "1.0";
}
void ConstantDecimalElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        lineEditValue = userInput->getString(key::lineEditValue);
    }
}
std::shared_ptr<ElementUserInputs> ConstantDecimalElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addString(key::lineEditValue, lineEditValue);
    return ret;
}
std::shared_ptr<AbstractElement> ConstantDecimalElement::clone() const
{
    auto ret = std::make_shared<ConstantDecimalElement>();
    ret->lineEditValue = lineEditValue;

    return ret;
}

std::shared_ptr<CodeText> ConstantDecimalElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    // static Value set
    ret->addToBody(lineEditValue);
    return ret;
}

QWidget* ConstantDecimalElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("take " + getName(), parent);
    wdg->setObjectName("ConstantDecimalGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#ConstantDecimalGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ConstantDecimalGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QVBoxLayout* wdgLayout = new QVBoxLayout(wdg);
    wdgLayout->setContentsMargins(0, 0, 0, 0);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLineEdit* staticValueLineEdit = new QLineEdit(wdg);
    staticValueLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(staticValueLineEdit, &QLineEdit::textChanged, [=](const QString& value) {
        lineEditValue = value;
        emit childValueChanged();
    });

    QCheckBox* addToUIcheckBox = new QCheckBox("add to UI", wdg);
    addToUIcheckBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QObject::connect(addToUIcheckBox, &QCheckBox::stateChanged, [=](int state) {
        if (state == Qt::Checked) {
            InputLabelDialog dialog("Parameter Label:", wdg);

            if (dialog.exec() == QDialog::Accepted) {
                // add staticValueLineEdit to parameter List, and it will auto matically remove widget from element Group box.
                emit updateParameterWidgets(staticValueLineEdit, true, dialog.getText()); 
            }

        } else {
            emit updateParameterWidgets(staticValueLineEdit, false); // Remove from parameter List staticValueLineEdit
            wdgLayout->addWidget(staticValueLineEdit);  // add again back to element Group box.
        }
    });

    staticValueLineEdit->setText(lineEditValue);
    
    wdgLayout->addWidget(addToUIcheckBox);
    wdgLayout->addWidget(staticValueLineEdit);

    return wdg;
}