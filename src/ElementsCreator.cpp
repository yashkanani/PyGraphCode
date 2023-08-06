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
#include "InputLabelDialog.h"
#include "ElementsControlButtons.h"

ElementsCreator::ElementsCreator(QWidget* parent)
    : QWidget(parent)
{
    setObjectName("elementsCreatorWidget");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    elementsListHolder = new ElementsListWidget(this);
    elementsListHolder->setElementsPerRow(8);
    layout->addWidget(elementsListHolder);


    ElementsControlButtons* controls = new ElementsControlButtons(this);
    controls->setObjectName("ElementsControlButtons");

    connect(controls, &ElementsControlButtons::addButtonClicked, this, &ElementsCreator::onAddVariableClicked);
    layout->addWidget(controls);

    setLayout(layout);
    
}


void ElementsCreator::onAddVariableClicked()
{
    InputLabelDialog dialog("Variable Name:", this);

    if (dialog.exec() == QDialog::Accepted) {
        QString variableName = dialog.getText();
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
