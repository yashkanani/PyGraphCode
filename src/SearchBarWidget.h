#ifndef SEARCHBARWIDGET_H
#define SEARCHBARWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class SearchBarWidget : public QFrame {
    Q_OBJECT

public:
    SearchBarWidget(QWidget* parent = nullptr);
signals:
    void searchTextChanged(const QString& text);

private:
    QHBoxLayout* searchBarLayout;
    QLabel* searchIconLabel;
    QLineEdit* searchLineEdit;
    QPushButton* searchClearButton;
};

#endif // SEARCHBARWIDGET_H
