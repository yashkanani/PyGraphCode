#include "ReadVariableElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "PlaceHolder.h"
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>


ReadVariableElement::ReadVariableElement()
{
    name = "Read Variable";
    image = QPixmap(":/resource/Variable.png");
    type = BasicElementType::READ_VARIABLE;

    methodSelectcomboBox = nullptr;
    staticValueLineEdit = nullptr;
    dynamicValueContainer = nullptr;
    
}



std::shared_ptr<AbstractElement> ReadVariableElement::clone() const
{
    return std::make_shared<ReadVariableElement>();
}

std::shared_ptr<CodeText> ReadVariableElement::getText() const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>();

    QString line;
    if (methodSelectcomboBox) {

        switch (methodSelectcomboBox->currentIndex()) {
        case 0: { 
            // Read
            line = "a";
            break;
        }
        case 1: {
            // Static Value set
            if (staticValueLineEdit) {
                line = "a = " + staticValueLineEdit->text();
            }
            break;
        }
        case 2: {
            // Dynamic Value set
            if (dynamicValueContainer) {
                line = "a = " + dynamicValueContainer->getText()->getResult();
            }
           
            break;
        }
        default: {
            break;
        }
        };
    }
    
    ret->addToBody(line);
    return ret;
}

QWidget* ReadVariableElement::getViewWidget(QWidget* parent)
{

    QGroupBox* wdg = new QGroupBox(getName()+ " Variable", parent);
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

    methodSelectcomboBox = new QComboBox(wdg);
    methodSelectcomboBox->addItem("Read");
    methodSelectcomboBox->addItem("Static");
    methodSelectcomboBox->addItem("Dynamic");
    methodSelectcomboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    wdgLayout->addWidget(methodSelectcomboBox);

    staticValueLineEdit = new QLineEdit(wdg);
    staticValueLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    staticValueLineEdit->hide(); // Initially hide the line edit
    QObject::connect(staticValueLineEdit, &QLineEdit::textChanged, this, &AbstractElement::childValueChanged);
    wdgLayout->addWidget(staticValueLineEdit);

    dynamicValueContainer = new BuilderContainer(wdg, true);

    // Set the accepted types for the BuilderContainer
    QList<BasicElementType> acceptedTypes = { BasicElementType::READ_VARIABLE, BasicElementType::CONDITIONS };
    dynamicValueContainer->setAcceptedTypes(acceptedTypes);
    dynamicValueContainer->setMaxElements(1);

    dynamicValueContainer->hide(); // Initially hide the builder container
    QObject::connect(dynamicValueContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLayout->addWidget(dynamicValueContainer);

    // Connect the combo box signal to a lambda function
    QObject::connect(methodSelectcomboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if ((staticValueLineEdit == nullptr) || (dynamicValueContainer == nullptr)) {
            return;
        }

        switch (index) {

        case 0: {
            // Neither static nor dynamic, hide both line edit and builder container
            staticValueLineEdit->hide();
            dynamicValueContainer->hide();
            break;
        }
        case 1: {
            // Show the line edit for entering static value
            staticValueLineEdit->show();
            dynamicValueContainer->hide();
            break;
        }
        case 2: {
            // Show the builder container for entering dynamic value
            staticValueLineEdit->hide();
            dynamicValueContainer->show();
            break;
        }
        default: {
            // Handle any other cases if needed
            break;
        }
        }

        emit childValueChanged();
    });

    return wdg;
}
