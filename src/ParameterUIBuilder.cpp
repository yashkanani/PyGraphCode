#include "ParameterUIBuilder.h"
#include "BuilderContainer.h"
#include <QLabel>
#include <QPushButton>

ParameterUIBuilder::ParameterUIBuilder(BuilderContainer* builderContainer, QWidget* parent)
    : QWidget(parent)
    , m_builderContainer(builderContainer)
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QPushButton("hello"));
    setLayout(mainLayout);

    if (m_builderContainer) {
        // Create a connection to add or remove elements when the builderContainer emits the signal
        connect(m_builderContainer, &BuilderContainer::updateParameterWidgets, this, &ParameterUIBuilder::updateParameterList);
    }
}

void ParameterUIBuilder::updateParameterList(QWidget* element, bool addWidget, QString label)
{
    if (addWidget) {
        addToUI(label, element);
    } else {
        removeFromUI(element);
    }
}

void ParameterUIBuilder::addToUI(QString label, QWidget* widget)
{
    if (!widgetLabelMap.contains(widget)) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        QLabel* labelWidget = new QLabel(label);
        rowLayout->addWidget(labelWidget);
        rowLayout->addWidget(widget);

        mainLayout->addLayout(rowLayout);
        widgetLabelMap.insert(widget, labelWidget);
    }
}

void ParameterUIBuilder::removeFromUI(QWidget* widget)
{
    if (widgetLabelMap.contains(widget)) {
        QHBoxLayout* rowLayout = nullptr;
        for (int i = 0; i < mainLayout->count(); ++i) {
            if (QLayoutItem* item = mainLayout->itemAt(i)) {
                if (QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(item->layout())) {
                    if (layout->indexOf(widget) >= 0) {
                        rowLayout = layout;
                        break;
                    }
                }
            }
        }

        if (rowLayout) {
            mainLayout->removeItem(rowLayout);

            QLabel* labelWidget = widgetLabelMap.take(widget);
            rowLayout->removeWidget(labelWidget);
            labelWidget->deleteLater();
        }
    }
}

void ParameterUIBuilder::clearWidgets()
{
    while (!widgetLabelMap.isEmpty()) {
        QWidget* widget = widgetLabelMap.keys().first();
        mainLayout->removeWidget(widget);

        QLabel* labelWidget = widgetLabelMap.take(widget);
        labelWidget->deleteLater();
    }
}