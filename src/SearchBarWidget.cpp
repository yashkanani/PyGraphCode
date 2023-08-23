#include "SearchBarWidget.h"

SearchBarWidget::SearchBarWidget(QWidget* parent)
    : QFrame(parent)
{
    // Create a layout for the search bar
    searchBarLayout = new QHBoxLayout(this);
    searchBarLayout->setContentsMargins(0, 0, 0, 0);
    searchBarLayout->setSpacing(5);

    // Create the search icon label
    searchIconLabel = new QLabel(this);
    QPixmap searchIconPixmap(":/resource/search.png"); // Replace with the path to your search icon
    searchIconLabel->setPixmap(searchIconPixmap.scaled(16, 16)); // Adjust the size as needed

    // Create the line edit for entering the search text
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Search");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &SearchBarWidget::searchTextChanged);


    // Create the search clear button
    searchClearButton = new QPushButton(this);

    // Add the search icon and line edit to the layout
    searchBarLayout->addWidget(searchIconLabel);
    searchBarLayout->addWidget(searchLineEdit);
    searchBarLayout->addWidget(searchClearButton);

    // Set the layout as the main layout for this widget
    setLayout(searchBarLayout);
    setObjectName("searchBarWidget");
}
