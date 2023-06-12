#include "ConstantTextElement.h"
#include "CodeText.h"
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>

ConstantTextElement::ConstantTextElement()
{
    name = "Constant Text";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::CONSTANT_TEXT;

    staticValueLineEdit = nullptr;
}

std::shared_ptr<AbstractElement> ConstantTextElement::clone() const
{
    return std::make_shared<ConstantTextElement>();
}

std::shared_ptr<CodeText> ConstantTextElement::getText() const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>();

    QString line;

    // static Value set
    if (staticValueLineEdit) {
        line = "\"" + staticValueLineEdit->text() + "\"";
    }

    ret->addToBody(line);
    return ret;
}

QWidget* ConstantTextElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("take " + getName(), parent);
    wdg->setObjectName("ConstantTextGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
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
        "}");

    QVBoxLayout* wdgLayout = new QVBoxLayout(wdg);
    wdgLayout->setContentsMargins(0, 0, 0, 0);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    staticValueLineEdit = new QLineEdit(wdg);
    staticValueLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(staticValueLineEdit, &QLineEdit::textChanged, this, &AbstractElement::childValueChanged);
    wdgLayout->addWidget(staticValueLineEdit);

    return wdg;
}