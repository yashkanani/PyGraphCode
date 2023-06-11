#ifndef READ_VARIABLE_ELEMENT_H
#define READ_VARIABLE_ELEMENT_H

#include "AbstractElement.h"


class ReadVariableElement : public AbstractElement {
public:
    ReadVariableElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

};

#endif // READ_VARIABLE_ELEMENT_H