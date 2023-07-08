#include "ElementsCreator.h"
#include "WriteVariableElement.h"
#include "ReadVariableElement.h"
#include <QDialog>
#include <QFormLayout>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <qlabel.h>
#include "ElementDragEventHandler.h"
#include "ElementsListWidget.h"

ElementsCreator::ElementsCreator(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QPushButton* addButton = new QPushButton("Add Variable", this);
    connect(addButton, &QPushButton::clicked, this, &ElementsCreator::onAddVariableClicked);
    layout->addWidget(addButton);

    elementsListHolder = new ElementsListWidget(this);
    elementsListHolder->setElementsPerRow(8);

    layout->addWidget(elementsListHolder);

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
    
    if ((element != nullptr) && (elementsListHolder != nullptr)) {
        elementsListHolder->addElement(element.get());
    }

    
}
