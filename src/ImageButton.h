#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QWidget>


class ImageButton : public QWidget {
    Q_OBJECT
public:
    ImageButton(QWidget* customWidget, const QString& text, const QString& labelObjectName, QWidget* parent = nullptr);

private:
    QWidget* m_customWidget;
};

#endif // IMAGEBUTTON_H
