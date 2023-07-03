#include "UserDefinedElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "ElementUserInputs.h"

#include <qcheckbox.h>
#include <qgroupbox.h>

namespace key {
const std::string usercontainerKey = "CustomInput";
}

UserDefinedElement::UserDefinedElement()
{
    name = "User Defined Element";
    image = QPixmap(":/resource/Operation.png");
    type = BasicElementType::USER_DEFINED;

    // Initialize other member variables
    userContainer = std::make_shared<BuilderContainer>(nullptr, true);
    isWidgetVisible = false;
}

void UserDefinedElement::setUserInput(std::shared_ptr<ElementUserInputs> userInput)
{
    if (userInput != nullptr) {
        userContainer = userInput->getContainer(key::usercontainerKey);
    }
}

std::shared_ptr<ElementUserInputs> UserDefinedElement::getUserInput()
{
    std::shared_ptr<ElementUserInputs> ret = std::make_shared<ElementUserInputs>();
    ret->addContainer(key::usercontainerKey, userContainer);
    return ret;
}

std::string UserDefinedElement::getUserInputkey()
{
    return key::usercontainerKey;
}

std::shared_ptr<AbstractElement> UserDefinedElement::clone() const
{
    auto ret = std::make_shared<UserDefinedElement>();

    ret->userContainer = std::make_shared<BuilderContainer>(nullptr, true);
    ret->userContainer->appendContainerInformationList(userContainer->getContainerInformation());

    return ret;
}

std::shared_ptr<CodeText> UserDefinedElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);

    ret = userContainer->getText(0);

    return ret;
}

QWidget* UserDefinedElement::getViewWidget(QWidget* parent)
{
    QGroupBox* groupBox = new QGroupBox("User Defined Element", parent);
    QVBoxLayout* layout = new QVBoxLayout(groupBox);

    // Create the check box for toggling the visibility of the container widget
    QCheckBox* checkBox = new QCheckBox("Toggle Widget", groupBox);
    layout->addWidget(checkBox);

    // Create the widget containing the BuilderContainer and its child widgets
    QWidget* containerWidget = new QWidget(groupBox);
    QVBoxLayout* containerLayout = new QVBoxLayout(containerWidget);

    if (userContainer != nullptr) {
        QObject::connect(userContainer.get(), &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
        containerLayout->addWidget(userContainer.get());
    }

    // Set the visibility of the container widget based on the check box state
    containerWidget->setVisible(checkBox->isChecked());

    // Connect the check box signal to the slot that toggles the visibility of the container widget
    QObject::connect(checkBox, &QCheckBox::stateChanged, [=](int state) {
        containerWidget->setVisible(state == Qt::Checked);
    });

    // Add the container widget to the layout
    layout->addWidget(containerWidget);

    return groupBox;
}