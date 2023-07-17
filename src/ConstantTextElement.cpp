#include "ConstantTextElement.h"
#include "CodeText.h"
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include "ElementUserInputs.h"
#include "ParameterUIBuilder.h"

namespace key {
    const std::string lineEditText = "inputText";
    
}


ConstantTextElement::ConstantTextElement()
{
    name = "Constant Text";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::CONSTANT_TEXT;

    lineEditText = "PyGraph";
}
void ConstantTextElement::updateParameterWidgets(ParameterUIBuilder* const parameterUIBuilder)
{
}
std::shared_ptr<AbstractElement> ConstantTextElement::clone() const
{
    auto ret = std::make_shared<ConstantTextElement>();
    ret->lineEditText = lineEditText;
    return ret;
}
void ConstantTextElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        lineEditText = userInput->getString(key::lineEditText);
    }
}
std::shared_ptr<ElementUserInputs> ConstantTextElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addString(key::lineEditText, lineEditText);
    return ret;
}
std::shared_ptr<CodeText> ConstantTextElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);

    QString line;

    // static Value set

    line = "\"" + lineEditText + "\"";

    ret->addToBody(line);
    return ret;
}

QWidget* ConstantTextElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("take " + getName(), parent);
    wdg->setObjectName("ConstantTextGroupBox");

    // Set the style sheet to customize the appearance
    /*wdg->setStyleSheet(
        "QGroupBox#ConstantTextGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ConstantTextGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");*/

    QVBoxLayout* wdgLayout = new QVBoxLayout(wdg);
    wdgLayout->setContentsMargins(0, 0, 0, 0);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLineEdit* staticValueLineEdit = new QLineEdit(wdg);
    staticValueLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(staticValueLineEdit, &QLineEdit::textChanged, [=](const QString& value) {
        lineEditText = value;
        emit childValueChanged();
    });
    staticValueLineEdit->setText(lineEditText);
    wdgLayout->addWidget(staticValueLineEdit);

    return wdg;
}