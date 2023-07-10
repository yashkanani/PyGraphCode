#ifndef INPUTLABELDIALOG_H
#define INPUTLABELDIALOG_H

#include <QDialog>
#include <QLineEdit>

class InputLabelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputLabelDialog(const QString& labelText, QWidget* parent = nullptr);
    QString getText() const;

private:
    QLineEdit* labelLineEdit;
};

#endif // INPUTLABELDIALOG_H
