#include "placeHolder.h"
#include "BuilderContainer.h"

#include <QVBoxLayout>
#include <QComboBox>

PlaceHolder::PlaceHolder(QWidget* parent, BuilderContainer* container)
    : QWidget(parent)
    , container(container)
{
    createWidgets();
}

BuilderContainer* PlaceHolder::getContainer()
{
    return container;
}

QString PlaceHolder::getComboBoxText()
{
    QComboBox* comboBox = findChild<QComboBox*>("comboBox");
    if (comboBox)
        return comboBox->currentText();
    else
        return QString();
}

void PlaceHolder::createWidgets()
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QComboBox* comboBox = new QComboBox();
    comboBox->addItem("Static");
    comboBox->addItem("Dynamic");
    comboBox->setObjectName("comboBox");
    layout->addWidget(comboBox);
    layout->addWidget(container);

    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 1) {
            container->show();
        } else {
            container->hide();
        }
    });
}

