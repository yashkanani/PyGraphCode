#include "WriteVariableElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "PlaceHolder.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>

WriteVariableElement::WriteVariableElement()
{
    name = "Write Variable";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::WRITE_VARIABLE;

    dynamicValueContainer = nullptr;
}

std::shared_ptr<AbstractElement> WriteVariableElement::clone() const
{
    return std::make_shared<WriteVariableElement>();
}

std::shared_ptr<CodeText> WriteVariableElement::getText() const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>();

    QString line;

    // Dynamic Value set
    if (dynamicValueContainer) {
        line = getName() + " = " + dynamicValueContainer->getText()->getResult();
    }

    ret->addToBody(line);
    return ret;
}

QWidget* WriteVariableElement::getViewWidget(QWidget* parent)
{

    QGroupBox* wdg = new QGroupBox("set " + getName(), parent);
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

    dynamicValueContainer = new BuilderContainer(wdg, true);

    // Set the accepted types for the BuilderContainer
    QList<BasicElementType> acceptedTypes = { BasicElementType::WRITE_VARIABLE, BasicElementType::CONDITIONS, BasicElementType::CONSTANT_TEXT, BasicElementType::CONSTANT_DECIMAL };
    dynamicValueContainer->setAcceptedTypes(acceptedTypes);
    dynamicValueContainer->setMaxElements(1);
    QObject::connect(dynamicValueContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLayout->addWidget(dynamicValueContainer);

    return wdg;
}
