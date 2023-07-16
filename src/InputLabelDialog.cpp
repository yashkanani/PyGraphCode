#include "InputLabelDialog.h"
#include <QFormLayout>
#include <QPushButton>

InputLabelDialog::InputLabelDialog(const QString& labelText, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Enter Name");

    QFormLayout* formLayout = new QFormLayout(this);
    labelLineEdit = new QLineEdit(this);
    formLayout->addRow(labelText, labelLineEdit);

    QPushButton* okButton = new QPushButton("OK", this);
    formLayout->addRow(okButton);

    connect(okButton, &QPushButton::clicked, this, &InputLabelDialog::accept);
}

QString InputLabelDialog::getText() const
{
    return labelLineEdit->text();
}
