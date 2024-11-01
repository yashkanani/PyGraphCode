#include "ImageButton.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>

ImageButton::ImageButton(QWidget* customWidget, const QString& text, const QString& labelObjectName, QWidget* parent)
    : QWidget(parent)
    , m_customWidget(customWidget)
{
    

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    //layout->setSpacing(0);

    if (m_customWidget) {
        m_customWidget->setParent(this);
        layout->addWidget(m_customWidget);
    }


    if (!text.isEmpty()) {
        QLabel* label = new QLabel(text, this);
        label->setObjectName(labelObjectName);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        layout->addWidget(label);
    }

    //layout->setAlignment(Qt::AlignHCenter);
    setLayout(layout);
}
