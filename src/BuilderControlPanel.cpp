#include "BuilderControlPanel.h"
#include <qscrollarea.h>
#include "BuilderContainer.h"
#include "ElementsCreator.h"
#include "ResultedTextView.h"
#include "ParameterUIBuilder.h"
#include "BuilderControlsButtons.h"
#include <qscrollbar.h>

BuilderControlPanel::BuilderControlPanel(ElementsListWidget* customElementWidget, QWidget* parent)
    : QWidget(parent)
{
    setObjectName("builderControlPanel");

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    QWidget* m_container = new QWidget(this);
    m_container->setObjectName("builderContainerHolder");

    QHBoxLayout* m_containerLay = new QHBoxLayout(m_container);
    m_containerLay->setContentsMargins(0, 0, 0, 0);

    QScrollArea* scrollBuilderArea = new QScrollArea(this);
    scrollBuilderArea->setWidgetResizable(true); // Allow the scroll area to resize the widget
    scrollBuilderArea->verticalScrollBar()->parent()->setProperty("background_transparent", true);
    scrollBuilderArea->horizontalScrollBar()->parent()->setProperty("background_transparent", true);

    BuilderContainer* builderContainer = new BuilderContainer(scrollBuilderArea);
    QObject::connect(builderContainer, &BuilderContainer::EnsureVisible, scrollBuilderArea, &QScrollArea::ensureVisible);
    scrollBuilderArea->setWidget(builderContainer);

    m_containerLay->addWidget(scrollBuilderArea);

    m_layout->addWidget(getButtonWidget(builderContainer, customElementWidget, this), 0, 0);
    m_layout->addWidget(m_container, 1, 0);
    m_layout->addWidget(createTabWidget(builderContainer), 0, 1,2,1);
   
    // Set the column stretch to distribute remaining space
    m_layout->setRowStretch(1, 1);
    m_layout->setColumnStretch(0, 2);
    m_layout->setColumnStretch(1, 1);

}


QTabWidget* BuilderControlPanel::createTabWidget(BuilderContainer* builderContainer)
{
    QTabWidget* tabWidget = new QTabWidget(this);

    QWidget* codeViewWidget = new QWidget(tabWidget);
    QGridLayout* codeViewLayout = new QGridLayout(codeViewWidget);
    codeViewLayout->setContentsMargins(0, 0, 0, 0);

    codeViewLayout->addWidget(getElementsCreatorWidget(codeViewWidget), 0, 0);
    codeViewLayout->addWidget(getResultedTextViewWidget(codeViewWidget, builderContainer), 1, 0);
    codeViewWidget->setLayout(codeViewLayout);


    ParameterUIBuilder* parameterHolderWidget = new ParameterUIBuilder(builderContainer, this);

    tabWidget->addTab(parameterHolderWidget, "Parameters");
    tabWidget->addTab(codeViewWidget, "SourceCode");
    
    return tabWidget;
}


QWidget* BuilderControlPanel::getResultedTextViewWidget(QWidget* parent, BuilderContainer* builderContainer)
{
    ResultedTextView* resultedTextView = new ResultedTextView(parent, builderContainer);
    return resultedTextView;
}

QWidget* BuilderControlPanel::getElementsCreatorWidget(QWidget* parent)
{
    ElementsCreator* elementsCreator = new ElementsCreator(parent);
    return elementsCreator;
}

QWidget* BuilderControlPanel::getButtonWidget(BuilderContainer* builderContainer, ElementsListWidget* customElementWidget, QWidget* parent)
{
    BuilderControlsButtons* controlButtons = new BuilderControlsButtons(builderContainer, customElementWidget, parent);
    return controlButtons;
}