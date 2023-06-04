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
    std::shared_ptr<CodeText> getText() const;

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

    std::shared_ptr<CodeText> getText(const ContainerInformation& containerInfo) const;
    int findInsertIndex(QDropEvent* event);
    

    AbstractElement* createInstance(const QString& elementType);
    bool isDropAccepted(const AbstractElement* element) const;
    void addElementWidget(QWidget* elementWidget, int insertIndex);

    QVBoxLayout* builderContainerlayout;
};

#endif // BUILDERCONTAINER_H