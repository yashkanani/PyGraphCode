#include "ElementsControlButtons.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "ImageButton.h"
#include "DeleteItem.h"

ElementsControlButtons::ElementsControlButtons(QWidget* parent)
    : QWidget(parent)
{
    

    
    // Create the "Add" button
    QPushButton* addButton = new QPushButton(this);
    addButton->setObjectName("elementsControlButtons_addbutton");

    // Create the horizontal layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(new ImageButton(addButton, "Add", "elementcontrol_imageButtonText", this));
    layout->addWidget(new ImageButton(new DeleteItem(":/resource/textcolor_empty_trash.png", ":/resource/textcolor_full_trash.png", this), "Remove", "elementcontrol_imageButtonText", this));
    layout->setAlignment(Qt::AlignTop); // Align button horizontally in the middle

    // Set the layout for the widget
    setLayout(layout);

    // Connect button signal to emit custom signal on click
    connect(addButton, &QPushButton::clicked, this, &ElementsControlButtons::addButtonClicked);
}
