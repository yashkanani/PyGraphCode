#include "imagebutton.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>

ImageButton::ImageButton(const QString &objectName, const QString &text, QWidget *parent)
    : QWidget(parent), m_objectName(objectName) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QPushButton *button = new QPushButton(this);
    button->setObjectName(m_objectName);

    connect(button, &QPushButton::clicked, this, &ImageButton::clicked);

    QLabel *label = new QLabel(text, this);
    label->setObjectName("imageButtonText");
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);

    layout->addWidget(button);
    layout->addWidget(label);

    layout->setAlignment(Qt::AlignHCenter);
    setLayout(layout);
}
