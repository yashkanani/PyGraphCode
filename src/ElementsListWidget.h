#ifndef ELEMENTSLISTWIDGET_H
#define ELEMENTSLISTWIDGET_H

#include <QWidget>

class QLabel;
class QGridLayout;
class QScrollArea;
class QAbstractScrollArea;
class AbstractElement;
class QTreeView;
class QStandardItemModel;
class QSortFilterProxyModel;

class ElementsListWidget : public QWidget {
    Q_OBJECT
public:
    ElementsListWidget(QWidget* parent = nullptr);

public:
    void addElement(AbstractElement* element);
    void setElementsPerRow(int numberOfelementsPerRow);

signals:
    void serachElement(const QString& text);

private:
    QTreeView* elementsListLayout;
    QSortFilterProxyModel* proxyModel;
    QStandardItemModel* model;
    //QGridLayout* elementsListLayout;
    int elementsPerRow;
    int totalElements;
};

#endif // ELEMENTSLISTWIDGET_H
