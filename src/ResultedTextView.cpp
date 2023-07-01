#include "ResultedTextView.h"
#include "CodeText.h"

ResultedTextView::ResultedTextView(QWidget* parent, BuilderContainer* builderContainer)
    : QWidget(parent), m_builderContainer(builderContainer)
{
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    m_resultedTextLabel = new QLabel(scrollArea);
    m_resultedTextLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_resultedTextLabel->setWordWrap(true);

    scrollArea->setWidget(m_resultedTextLabel);

    if (m_builderContainer) {
        // Create a connection to update the text label when the builderContainer emits the signal
        QObject::connect(m_builderContainer, &BuilderContainer::updateResultedTextView, this, &ResultedTextView::updateText);
    }

    updateText(); // Update the text initially

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(scrollArea);
}

void ResultedTextView::updateText()
{
    if (m_builderContainer) {
        std::shared_ptr<CodeText> result = m_builderContainer->getText(0);
        m_resultedTextLabel->setText(result->getResult());
    }
}