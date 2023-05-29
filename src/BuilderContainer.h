#ifndef BUILDERCONTAINER_H
#define BUILDERCONTAINER_H

#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "AbstractElement.h"
#include "ContainerInformation.h"

class BuilderContainer : public QWidget {
    Q_OBJECT

public:
    explicit BuilderContainer(QWidget* parent = nullptr);
    QString getText() const;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    ContainerInformation containerInformation;

    QRect dropIndicatorRect;
    bool isDropIndicatorVisible = false;
    void hideDropIndicator();
    void updateDropIndicator(int insertIndex);

    QRect calculateDropIndicatorRect(int insertIndex) const;

    QString getText(const ContainerInformation& containerInfo) const;
    int findInsertIndex(QDropEvent* event);
    

    AbstractElement* createInstance(const QString& elementType);
    bool isDropAccepted(const AbstractElement* element) const;
    void addElementWidget(QWidget* elementWidget, int insertIndex);

    QVBoxLayout* builderContainerlayout;
};

#endif // BUILDERCONTAINER_H