#include "ParameterUIBuilder.h"
#include "BuilderContainer.h"

ParameterUIBuilder::ParameterUIBuilder(BuilderContainer* builderContainer, QWidget* parent)
    : QWidget(parent)
    , m_builderContainer(builderContainer)
{
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    if (m_builderContainer) {
        // Create a connection to add or remove elements when the builderContainer emits the signal
        QObject::connect(m_builderContainer, &BuilderContainer::updateParameterWidgets, this, &ParameterUIBuilder::updateParameterList);
    }
}

void ParameterUIBuilder::updateParameterList(QWidget* element, bool addWidget, QString label)
{
    if (addWidget && (label.isEmpty() == false)) {
        addToUI(label, element);
    } else {
        removeFromUI(element);
    }
}

void ParameterUIBuilder::addToUI(QString label, QWidget* widget)
{
    if ((widget != nullptr) && (widgetList.contains(widget) == false)) {
        mainLayout->addWidget(widget);
        widgetList.append(widget);
    }

}

void ParameterUIBuilder::removeFromUI(QWidget* widget)
{
    if ((widget != nullptr) && (widgetList.contains(widget) == true)) {
        mainLayout->removeWidget(widget);
        widgetList.removeOne(widget);
    }
}

void ParameterUIBuilder::clearWidgets()
{
    while (!widgetList.isEmpty())
    {
        QWidget *widget = widgetList.takeLast();
        mainLayout->removeWidget(widget);
    }
}
