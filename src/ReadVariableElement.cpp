#include "ReadVariableElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "PlaceHolder.h"
#include <qlabel.h>
#include <qgroupbox.h>
#include <qlayout.h>

#include <qwidget.h>

#include <qpushbutton.h>


ReadVariableElement::ReadVariableElement()
{
    name = "Read Variable";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::READ_VARIABLE;
}



std::shared_ptr<AbstractElement> ReadVariableElement::clone() const
{
    return std::make_shared<ReadVariableElement>();
}

std::shared_ptr<CodeText> ReadVariableElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    ret->addToBody(getName());
    return ret;
}

QWidget* ReadVariableElement::getViewWidget(QWidget* parent)
{

    QGroupBox* wdg = new QGroupBox("Read", parent);
    wdg->setObjectName("ReadVariableGroupBox");

   

     // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#ReadVariableGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ReadVariableGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}"
        );
    QVBoxLayout* wdgLayout = new QVBoxLayout(wdg);
    wdgLayout->setContentsMargins(1, 1, 1, 1);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel* displayLabel = new QLabel(getName(), wdg);
    displayLabel->setObjectName("readVariableNameText");
    displayLabel->setStyleSheet(
        "QLabel#readVariableNameText{"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "}"
    );
    displayLabel->setAlignment(Qt::AlignCenter); // Align the label's text to the center
    wdgLayout->addWidget(displayLabel);
    

    

    return wdg;
}
