#ifndef DELETEITEM_H
#define DELETEITEM_H

#include <QWidget>
#include <QMimeData>
#include <QVariant>
#include <QPixmap>

class DeleteItem : public QWidget {
    Q_OBJECT

public:
    explicit DeleteItem(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    

private:
    QPixmap openPixmap;
    QPixmap closePixmap;
    bool isDustbinOpen;
};

#endif // DELETEITEM_H
