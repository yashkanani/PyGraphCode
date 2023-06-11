#include "ElementsCreator.h"
#include "WriteVariableElement.h"
#include "ReadVariableElement.h"
#include "elementscreator.h"
#include <QDialog>
#include <QFormLayout>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <qlabel.h>
#include "ElementDragEventHandler.h"

#include "ElementManager.h"

ElementsCreator::ElementsCreator(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* addButton = new QPushButton("Add Variable", this);
    connect(addButton, &QPushButton::clicked, this, &ElementsCreator::onAddVariableClicked);
    layout->addWidget(addButton);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    QWidget* scrollContentWidget = new QWidget(scrollArea);
    variableListLayout = new QGridLayout(scrollContentWidget);
    scrollArea->setWidget(scrollContentWidget);

    layout->addWidget(scrollArea);

    setLayout(layout);
}

void ElementsCreator::onAddVariableClicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Enter Variable Name");

    QFormLayout formLayout(&dialog);
    QLineEdit nameLineEdit(&dialog);
    formLayout.addRow("Variable Name:", &nameLineEdit);

    QPushButton okButton("OK", &dialog);
    connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    formLayout.addRow(&okButton);

    if (dialog.exec() == QDialog::Accepted) {
        QString variableName = nameLineEdit.text();

        addReadVariableElement(variableName);
        addWriteVariableElement(variableName);
    }
}

void ElementsCreator::addReadVariableElement(const QString& variableName) {
    std::shared_ptr<ReadVariableElement> variableElement = std::make_shared<ReadVariableElement>();
    variableElement->setName(variableName);

    // Add custom variable for future use.
    customeReadVariables.push_back(variableElement);

    addElement(variableElement);
    }
void ElementsCreator::addWriteVariableElement(const QString& variableName) {
    std::shared_ptr<WriteVariableElement> variableElement = std::make_shared<WriteVariableElement>();
    variableElement->setName(variableName);

    // Add custom variable for future use.
    customeWriteVariables.push_back(variableElement);

    addElement(variableElement);
}

void ElementsCreator::addElement(std::shared_ptr<AbstractElement> element)
{
    
    if (element) {
        // Get the image from the variableElement
        QPixmap variableImage = element->getImage();

        QLabel* elementIconLabel = new QLabel(this);

        elementIconLabel->setAlignment(Qt::AlignCenter);
        elementIconLabel->setStyleSheet("QLabel:hover { background-color: lightgray; }");
        elementIconLabel->setProperty("element", QVariant::fromValue(static_cast<AbstractElement*>(element.get())));
        elementIconLabel->setCursor(Qt::OpenHandCursor);
        elementIconLabel->setAlignment(Qt::AlignCenter);
        elementIconLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        elementIconLabel->installEventFilter(new ElementDragEventHandler(elementIconLabel)); // Install event filter
        elementIconLabel->setPixmap(element->getImage().scaled(50, 50));

        // Add the element icon label to the grid layout at the appropriate position
        variableListLayout->addWidget(elementIconLabel, rowCount, columnCount);
        variableListLayout->setRowStretch(variableListLayout->rowCount(), 1);

        // Increment the column count and move to the next row if necessary
        columnCount++;
        if (columnCount >= 8) {
            columnCount = 0;
            rowCount++;
        }
    }

    
}