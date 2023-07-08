#ifndef CUSTOMELEMENTINPUTDIALOG_H
#define CUSTOMELEMENTINPUTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QLineEdit>

class CustomElementInputDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomElementInputDialog(QWidget* parent = nullptr);

    QString getCustomElementName() const;
    QString getSaveLocation() const;

private slots:
    void handleBrowseButtonClicked();

private:
    QLineEdit* nameLineEdit;
    QLineEdit* saveLocationLineEdit;
    QPushButton* browseButton;
};

#endif // CUSTOMELEMENTINPUTDIALOG_H
