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
class QStandardItem;


class ElementsListWidget : public QWidget {
    Q_OBJECT
public:
    ElementsListWidget(QWidget* parent = nullptr);

public:
    void addElement(AbstractElement* element);
    void setElementsPerRow(int numberOfelementsPerRow);

public slots:
    void serachElement(const QString& text);

private slots:
   

private:
    QTreeView* elementsListLayout;
    QStandardItemModel* sourceModel;
   
    //QGridLayout* elementsListLayout;
    int elementsPerRow;
    int totalModelElements;

    QVector<AbstractElement*> elementsModel;

   
    void clearModel();
    void showWidgetOnView(QWidget* elementDisplayUnit);
    QWidget* createDisplayUnit(AbstractElement* element);
};

#endif // ELEMENTSLISTWIDGET_H
