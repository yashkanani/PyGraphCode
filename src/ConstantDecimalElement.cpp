#include "CodeText.h"
#include "ConstantDecimalElement.h"
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>

ConstantDecimalElement::ConstantDecimalElement()
{
    name = "Constant Number";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::CONSTANT_DECIMAL;

    staticValueLineEdit = nullptr;
}

std::shared_ptr<AbstractElement> ConstantDecimalElement::clone() const
{
    return std::make_shared<ConstantDecimalElement>();
}

std::shared_ptr<CodeText> ConstantDecimalElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    // static Value set
    if (staticValueLineEdit) {
        ret->addToBody(staticValueLineEdit->text());
    }
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

    staticValueLineEdit = new QLineEdit(wdg);
    staticValueLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(staticValueLineEdit, &QLineEdit::textChanged, this, &AbstractElement::childValueChanged);
    wdgLayout->addWidget(staticValueLineEdit);

    return wdg;
}