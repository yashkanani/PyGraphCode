#include "BuilderControlsButtons.h"
#include "BuilderContainer.h"
#include "CustomElementInputDialog.h"
#include "ElementManager.h"
#include "ElementsListWidget.h"
#include "JSONDataHandler.h"

#include <QtWidgets>

BuilderControlsButtons::BuilderControlsButtons(BuilderContainer* builderContainer, ElementsListWidget* customElementWidget, QWidget* parent)
    : QWidget(parent)
    , m_builderContainer(builderContainer)
    , m_customElementWidget(customElementWidget)
{
    // Create the buttons
    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* loadButton = new QPushButton("Load", this);

    // Create the horizontal layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

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
        CustomElementInputDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            QString customElementName = dialog.getCustomElementName();
            QString filePath = dialog.getSaveLocation();

            // Check if the filePath is empty
            if (filePath.isEmpty()) {
                qDebug() << "File path is empty.";
                return;
            }

            // Append the custom element name to the file path
            filePath += QDir::separator() + customElementName + ".json";

            // create the packet for json file.
            JSONDataHandler::JSONContainerHeader jsonPacket;
            jsonPacket.displayName = customElementName;
            jsonPacket.containerinformationList = m_builderContainer->getContainerInformation();

            // Save Container information in file.
            JSONDataHandler().saveContainerInformationListToJsonFile(jsonPacket, filePath);

            // Verify the result
            JSONDataHandler::JSONContainerHeader resultedJsonPacket = JSONDataHandler().readContainerInformationListFromJsonFile(filePath);

            // Create the Custom Element and added in Customelement Widget.
            std::shared_ptr<AbstractElement> customElement = ElementManager::getInstance().createCustomElement(resultedJsonPacket.displayName, resultedJsonPacket.containerinformationList);
            m_customElementWidget->addElement(customElement.get());

            qDebug() << "JSON data written to file successfully.";
        }
    }
}

void BuilderControlsButtons::handleLoadButtonClicked()
{
    // Use the builderContainer pointer here
    if (m_customElementWidget) {

        // Open file dialog for JSON file selection
        QStringList fileNames = QFileDialog::getOpenFileNames(nullptr, "Select JSON Files", "", "JSON Files (*.json)");

        // Process each selected file
        for (const QString& filePath : fileNames) {
            
            JSONDataHandler::JSONContainerHeader jsonPacket = JSONDataHandler().readContainerInformationListFromJsonFile(filePath);

            // Create the Custom Element and added in Customelement Widget.
            std::shared_ptr<AbstractElement> customElement = ElementManager::getInstance().createCustomElement(jsonPacket.displayName, jsonPacket.containerinformationList);
            m_customElementWidget->addElement(customElement.get());
        }

        return;
    }
}
