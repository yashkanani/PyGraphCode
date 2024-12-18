#include "ParameterUIBuilder.h"
#include "BuilderContainer.h"
#include <QLabel>
#include <QPushButton>
#include <qscrollarea.h>

ParameterUIBuilder::ParameterUIBuilder(BuilderContainer* builderContainer, QWidget* parent)
    : QWidget(parent)
    , m_builderContainer(builderContainer)
{

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    scrollArea->setWidgetResizable(true);

    // This widget is help to add the Stretch at the end;
    QWidget* holder = new QWidget(scrollArea);
    QVBoxLayout* holderLay = new QVBoxLayout(holder);

    QWidget* parameterWidget = new QWidget(holder);
    parameterLay = new QVBoxLayout(parameterWidget);
    holderLay->addWidget(parameterWidget);
    holderLay->addStretch();

    scrollArea->setWidget(holder);

    mainLayout->addWidget(scrollArea);

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
        rowLayout->addWidget(labelWidget, 0, Qt::AlignRight);
        rowLayout->addWidget(widget, 0, Qt::AlignLeft);
      

        parameterLay->addLayout(rowLayout);
        parameterLay->setAlignment(rowLayout,  Qt::AlignHCenter);

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