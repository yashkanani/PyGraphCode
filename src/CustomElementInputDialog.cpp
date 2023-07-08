#include "CustomElementInputDialog.h"
#include <QFormLayout>
#include <QPushButton>

CustomElementInputDialog::CustomElementInputDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Enter Custom Element Name");

    // Create the layout
    QFormLayout* formLayout = new QFormLayout(this);

    // Create the line edit for entering the name
    nameLineEdit = new QLineEdit(this);

    // Add the line edit to the layout
    formLayout->addRow("Name:", nameLineEdit);

    // Create the line edit for entering the save location
    saveLocationLineEdit = new QLineEdit(this);

    // Create the browse button
    browseButton = new QPushButton("Browse", this);

    // Connect the browse button to the slot
    connect(browseButton, &QPushButton::clicked, this, &CustomElementInputDialog::handleBrowseButtonClicked);

    // Create a horizontal layout for the save location
    QHBoxLayout* saveLocationLayout = new QHBoxLayout;
    saveLocationLayout->addWidget(saveLocationLineEdit);
    saveLocationLayout->addWidget(browseButton);

    // Add the save location layout to the form layout
    formLayout->addRow("Save Location:", saveLocationLayout);

    // Create the OK and Cancel buttons
    QPushButton* okButton = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    // Connect the buttons to the respective slots
    connect(okButton, &QPushButton::clicked, this, &CustomElementInputDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &CustomElementInputDialog::reject);

    // Add the buttons to the layout
    formLayout->addWidget(okButton);
    formLayout->addWidget(cancelButton);
}

QString CustomElementInputDialog::getCustomElementName() const
{
    return nameLineEdit->text();
}

QString CustomElementInputDialog::getSaveLocation() const
{
    return saveLocationLineEdit->text();
}

void CustomElementInputDialog::handleBrowseButtonClicked()
{
    QString saveDirectory = QFileDialog::getExistingDirectory(this, "Select Save Directory");
    saveLocationLineEdit->setText(saveDirectory);
}
