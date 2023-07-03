#include "BuilderControlsButtons.h"
#include "BuilderContainer.h"
#include "ElementsListWidget.h"
#include "JSONDataHandler.h"
#include "UserDefinedElement.h"
#include "ElementUserInputs.h"
#include "ElementManager.h"
#include "CustomElementInputDialog.h"

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

            JSONDataHandler().saveContainerInformationListToJsonFile(m_builderContainer->getContainerInformation(), filePath);
            
            qDebug() << "JSON data written to file successfully.";
        }
    }
}


void BuilderControlsButtons::handleLoadButtonClicked()
{
    // Use the builderContainer pointer here
    if (m_customElementWidget) {
        QString filePath = "C:/Users/yash0/Desktop/hh.json";
        auto customElement = ElementManager::getInstance().createCustomElement((JSONDataHandler().readContainerInformationListFromJsonFile(filePath)));
        m_customElementWidget->addElement(customElement.get());
        return;
    }

}
