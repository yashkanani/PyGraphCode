#ifndef READ_VARIABLE_ELEMENT_H
#define READ_VARIABLE_ELEMENT_H

#include "AbstractElement.h"


class ReadVariableElement : public AbstractElement {
public:
    ReadVariableElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
    void setUserInput(std::shared_ptr<ElementUserInputs> userInput) override;
    std::shared_ptr<ElementUserInputs> getUserInput() override;
};

#endif // READ_VARIABLE_ELEMENT_H