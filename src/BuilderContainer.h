#ifndef BUILDERCONTAINER_H
#define BUILDERCONTAINER_H

#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "AbstractElement.h"
#include "ContainerInformation.h"
#include <qframe.h>

class BuilderContainer : public QFrame {
    Q_OBJECT

public:
    explicit BuilderContainer(QWidget* parent = nullptr, bool isSubContainer = false);
    std::shared_ptr<CodeText> getText(int indentLevel) const;
    void setAcceptedTypes(const QList<BasicElementType>& acceptedTypes);
    void setMaxElements(int maxElements);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void updateResultedTextView();

private:
    ContainerInformation containerInformation;

    QRect dropIndicatorRect;
    bool isDropIndicatorVisible = false;
    void hideDropIndicator();
    void drawArrows();
    void updateDropIndicator(int insertIndex);


    QRect calculateDropIndicatorRect(int insertIndex) const;

    std::shared_ptr<CodeText> getText(const ContainerInformation& containerInfo, int indentLevel) const;
    int findInsertIndex(QDropEvent* event);
    

    bool isDropAccepted(const BasicElementType& elementType) const;
    bool isMaxElementsReached() const;
    void addElementWidget(QWidget* elementWidget, int insertIndex);

    QVBoxLayout* builderContainerlayout;
    QList<BasicElementType> acceptedTypes;
    int maxElements;
};

#endif // BUILDERCONTAINER_H