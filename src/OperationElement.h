#ifndef OPERATIONELEMENT_H
#define OPERATIONELEMENT_H

#include "AbstractElement.h"

class OperationElement : public AbstractElement {
public:
    OperationElement();

    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;



};

#endif // OPERATIONELEMENT_H