#ifndef BUILDERCONTAINER_H
#define BUILDERCONTAINER_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>

#include "AbstractElement.h"

class BuilderContainer : public QWidget
{
    Q_OBJECT

public:
    explicit BuilderContainer(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    AbstractElement* createInstance(const QString& elementType);
    bool isDropAccepted(const AbstractElement* element) const;
    void addElement(AbstractElement* element);

    QVBoxLayout* layout;
};

#endif // BUILDERCONTAINER_H