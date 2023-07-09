#ifndef BUILDERCONTAINER_H
#define BUILDERCONTAINER_H

#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "BasicElementType.h"
#include "ContainerInformation.h"
#include <qframe.h>

class CodeText;
class BuilderContainer : public QFrame {
    Q_OBJECT

public:
    explicit BuilderContainer(QWidget* parent = nullptr, bool isSubContainer = false);
    std::shared_ptr<CodeText> getText(int indentLevel) const;
    void setAcceptedTypes(const QList<BasicElementType>& acceptedTypes);
    void setMaxElements(int maxElements);
    void removeElementFromContainerInformation(const AbstractElement* element);
    const ContainerInformationList& getContainerInformation() const;
    void appendContainerInformationList(const ContainerInformationList& informationList, int insertIndex = 0);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void updateResultedTextView();
    void EnsureVisible(int xPosition, int yPosition, int xmargin = 50, int ymargin = 50);
    void updateParameterWidgets(QWidget* element, bool addWidget, QString label = "");

private:
    ContainerInformationList containerInformationList;

    QRect dropIndicatorRect;
    bool isDropIndicatorVisible = false;
    void hideDropIndicator();
    void drawArrows();
    void updateDropIndicator(int insertIndex);

    QRect calculateDropIndicatorRect(int insertIndex) const;
    int findInsertIndex(QDropEvent* event);

    bool isDropAccepted(const BasicElementType& elementType) const;
    bool isMaxElementsReached() const;
    void addElementWidget(QWidget* elementWidget, int insertIndex);
    void addInformationAndView(std::shared_ptr<AbstractElement> element, int insertIndex);

    QVBoxLayout* builderContainerlayout;
    QList<BasicElementType> acceptedTypes;
    int maxElements;
};

#endif // BUILDERCONTAINER_H