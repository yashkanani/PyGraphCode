#include "ParameterUIBuilder.h"
#include "BuilderContainer.h"
#include <QLabel>
#include <QPushButton>


ParameterUIBuilder::ParameterUIBuilder(BuilderContainer* builderContainer, QWidget* parent)
    : QWidget(parent)
    , m_builderContainer(builderContainer)
{

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QWidget* parameterWidget = new QWidget(this);
    parameterLay = new QVBoxLayout(parameterWidget);

    mainLayout->addWidget(parameterWidget);
    mainLayout->addStretch();

    setLayout(mainLayout);

    if (m_builderContainer) {
        // Create a connection to add or remove elements when the builderContainer emits the signal
        connect(m_builderContainer, &BuilderContainer::notifyToParameterWidgets, this, &ParameterUIBuilder::updateParameterList);
    }
}

void ParameterUIBuilder::updateParameterList()
{
   
    if (m_builderContainer) {
        m_builderContainer->updateParameterWidgets(this);
    }

    // New UPdateParameter UI Funcation Needs too call.
}

void ParameterUIBuilder::addToUI(QString label, QWidget* widget)
{
    if (!widgetLabelMap.contains(widget) && widget && (widget->parent() != nullptr)) {

        // Connect the destroyed signal of the widget's parent to handleParentDestroyed slot
        originalParents.insert(widget, widget->parent());
        connect(widget->parent(), &QObject::destroyed, this, &ParameterUIBuilder::handleParentDestroyed);

        QHBoxLayout* rowLayout = new QHBoxLayout();
        QLabel* labelWidget = new QLabel(label);
        rowLayout->addWidget(labelWidget);
        rowLayout->addWidget(widget);

        parameterLay->addLayout(rowLayout);
        widgetLabelMap.insert(widget, labelWidget);
    }
}

void ParameterUIBuilder::removeFromUI(QWidget* widget)
{
    if (widgetLabelMap.contains(widget)) {
        QHBoxLayout* rowLayout = nullptr;
        for (int i = 0; i < parameterLay->count(); ++i) {
            if (QLayoutItem* item = parameterLay->itemAt(i)) {
                if (QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(item->layout())) {
                    if (layout->indexOf(widget) >= 0) {
                        rowLayout = layout;
                        break;
                    }
                }
            }
        }

        if (rowLayout) {
            parameterLay->removeItem(rowLayout);

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
        parameterLay->removeWidget(widget);

        QLabel* labelWidget = widgetLabelMap.take(widget);
        labelWidget->deleteLater();
    }
}

void ParameterUIBuilder::handleParentDestroyed(QObject* parentObj)
{
    QWidget* parent = qobject_cast<QWidget*>(parentObj);

    for (auto it = originalParents.begin(); it != originalParents.end(); ++it) {
        if (it.value() == parent) {
            QWidget* widget = it.key();
            removeFromUI(widget);
            widget->deleteLater();
            break;
        }
    }
}