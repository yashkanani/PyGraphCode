import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    //width: 300
    //height: 40

    Row {
        spacing: 5

        Image {
            source: "qrc:/resource/search.png" // Replace with the actual path to your search icon
            width: 16
            height: 16
        }

        TextField {
            id: searchField
            placeholderText: "Search"
            width: parent ? parent.width - searchIcon.width : 260
            onTextChanged: {
                searchTextChanged(searchField.text)
            }
        }
    }

    // Signal to indicate search text change event
    signal searchTextChanged(string searchText)

}