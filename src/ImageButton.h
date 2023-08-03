#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QWidget>


class ImageButton : public QWidget {
    Q_OBJECT
public:
    ImageButton(const QString &objectName, const QString &text, QWidget *parent = nullptr);

signals: 
    void clicked(bool checked = false);

private:
    QString m_objectName;
};

#endif // IMAGEBUTTON_H
