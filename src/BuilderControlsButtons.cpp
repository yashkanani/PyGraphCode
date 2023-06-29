#include "BuilderControlsButtons.h"
#include <QtWidgets>
#include "BuilderContainer.h"
#include "JSONDataHandler.h"

BuilderControlsButtons::BuilderControlsButtons(BuilderContainer* builderContainer, QWidget* parent)
    : QWidget(parent), m_builderContainer(builderContainer)
{
    // Create the buttons
    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* loadButton = new QPushButton("Load", this);

    // Create the horizontal layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->setAlignment(Qt::AlignHCenter);  // Align buttons horizontally in the middle

    // Set the layout for the widget
    setLayout(layout);

    // Connect button signals to slots or actions as needed
    connect(saveButton, &QPushButton::clicked, this, &BuilderControlsButtons::handleSaveButtonClicked);
    connect(loadButton, &QPushButton::clicked, this, &BuilderControlsButtons::handleLoadButtonClicked);
}

void BuilderControlsButtons::handleSaveButtonClicked()
{
    // Use the builderContainer pointer here
    if (m_builderContainer)
    {
        auto rootObject = JSONDataHandler().convertContainerInformationListToJson(m_builderContainer->getContainerInformation());
        QJsonDocument jsonDocument(rootObject);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

        QString filePath = "C:/Users/yash0/Desktop/testJson.json"; // Specify the desired file path

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream textStream(&file);
            textStream << jsonString;
            file.close();
            qDebug() << "JSON data written to file successfully.";
        } else {
            qDebug() << "Failed to open the file for writing.";
        }
    }
}

void BuilderControlsButtons::handleLoadButtonClicked()
{
    // Use the builderContainer pointer here
    if (m_builderContainer)
    {
        QString filePath = "C:/Users/yash0/Desktop/testJson.json";
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open the file for reading.";
            return;
        }

        QString jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8());
        if (jsonDocument.isNull()) {
            qDebug() << "Failed to parse JSON document.";
            return;
        }

        QJsonObject rootObject = jsonDocument.object();
        JSONDataHandler dataHandler;
        dataHandler.convertJsonToContainerInformationList(rootObject);
        m_builderContainer->appendContainerInformationList(dataHandler.convertJsonToContainerInformationList(rootObject));
        return; 
    }

    // Create the BuilderInformation container
    // Read the Json object
    // create the Elements
    // plce information in 
}
