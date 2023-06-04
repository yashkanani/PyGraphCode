#ifndef OPERATIONELEMENT_H
#define OPERATIONELEMENT_H

#include "AbstractElement.h"

class OperationElement : public AbstractElement {
public:
    OperationElement();

    QString getName() const override;
    QPixmap getImage() const override;
    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    QString name;
    QPixmap image;
};

#endif // OPERATIONELEMENT_H