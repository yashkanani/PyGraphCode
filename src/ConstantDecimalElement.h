#ifndef CONSTANT_DECIMAL_ELEMENT_H
#define CONSTANT_DECIMAL_ELEMENT_H

#include "AbstractElement.h"

class QLineEdit;

class ConstantDecimalElement : public AbstractElement {
public:
    ConstantDecimalElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    QLineEdit* staticValueLineEdit;
};

#endif // CONSTANT_DECIMAL_ELEMENT_H