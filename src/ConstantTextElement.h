#ifndef CONSTANT_TEXT_ELEMENT_H
#define CONSTANT_TEXT_ELEMENT_H

#include "AbstractElement.h"

class QLineEdit;

class ConstantTextElement : public AbstractElement {
public:
    ConstantTextElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
    void setUserInput(std::shared_ptr<ElementUserInputs> userInput) override;
    std::shared_ptr<ElementUserInputs> getUserInput() override;
    void updateParameterWidgets(ParameterUIBuilder* const parameterUIBuilder) override;


private:
    QString lineEditText;
};

#endif // CONSTANT_TEXT_ELEMENT_H