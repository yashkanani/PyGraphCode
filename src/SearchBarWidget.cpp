#include "SearchBarWidget.h"

SearchBarWidget::SearchBarWidget(QWidget* parent)
    : QFrame(parent)
{
    // Create a layout for the search bar
    searchBarLayout = new QHBoxLayout(this);
    searchBarLayout->setContentsMargins(0, 0, 0, 0);
    searchBarLayout->setSpacing(0);

    // Create the search icon label
    searchIconLabel = new QLabel(this);
    searchIconLabel->setObjectName("searchIcon");
    QPixmap searchIconPixmap(":/resource/search_glass_icon.png"); // Replace with the path to your search icon
    searchIconLabel->setPixmap(searchIconPixmap);

    // Create the line edit for entering the search text
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setObjectName("searchLineEdit");
    searchLineEdit->setPlaceholderText("Search");
    


    // Create the search clear button
    searchClearButton = new QPushButton(this);
    searchClearButton->setObjectName("searchClearButton");
    searchClearButton->setIcon(QIcon(":/resource/search_clear_button.png"));
    searchClearButton->hide();
    
    // Add the search icon and line edit to the layout
    searchBarLayout->addWidget(searchIconLabel);
    searchBarLayout->addWidget(searchLineEdit);
    searchBarLayout->addWidget(searchClearButton);

    // Set the layout as the main layout for this widget
    setLayout(searchBarLayout);
    setObjectName("searchBarWidget");

    QObject::connect(searchClearButton, &QPushButton::clicked, this, [=]() {
        searchLineEdit->clear();
    });

    connect(searchLineEdit, &QLineEdit::textChanged, this, [=](const QString& text) {
        if (text.isEmpty()) {
            searchClearButton->hide();
        } else {
            searchClearButton->show();
        }
        emit searchTextChanged(text);
    });
}
