#include "BuilderControlsButtons.h"
#include "BuilderContainer.h"
#include "JSONDataHandler.h"
#include <QtWidgets>

BuilderControlsButtons::BuilderControlsButtons(BuilderContainer* builderContainer, QWidget* parent)
    : QWidget(parent)
    , m_builderContainer(builderContainer)
{
    // Create the buttons
    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* loadButton = new QPushButton("Load", this);

    // Create the horizontal layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->setAlignment(Qt::AlignHCenter); // Align buttons horizontally in the middle

    // Set the layout for the widget
    setLayout(layout);

    // Connect button signals to slots or actions as needed
    connect(saveButton, &QPushButton::clicked, this, &BuilderControlsButtons::handleSaveButtonClicked);
    connect(loadButton, &QPushButton::clicked, this, &BuilderControlsButtons::handleLoadButtonClicked);
}

void BuilderControlsButtons::handleSaveButtonClicked()
{
    // Use the builderContainer pointer here
    if (m_builderContainer) {
        QString filePath = "C:/Users/yash0/Desktop/testJson.json"; // Specify the desired file path
        auto rootObject = JSONDataHandler().saveContainerInformationListToJsonFile(m_builderContainer->getContainerInformation(), filePath);
    }
}

void BuilderControlsButtons::handleLoadButtonClicked()
{
    // Use the builderContainer pointer here
    if (m_builderContainer) {
        QString filePath = "C:/Users/yash0/Desktop/testJson.json";
        m_builderContainer->appendContainerInformationList(JSONDataHandler().readContainerInformationListFromJsonFile(filePath));
        return;
    }

    // Create the BuilderInformation container
    // Read the Json object
    // create the Elements
    // plce information in
}
