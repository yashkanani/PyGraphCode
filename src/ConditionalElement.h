#ifndef CONDITIONAL_ELEMENT_H
#define CONDITIONAL_ELEMENT_H

#include "AbstractElement.h"

class BuilderContainer;
class QComboBox;
class ConditionalElement : public AbstractElement {
public:
    ConditionalElement();
    std::shared_ptr<AbstractElement> clone() const override;
    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
    void setUserInput(std::shared_ptr<ElementUserInputs> userInput) override;
    std::shared_ptr<ElementUserInputs> getUserInput() override;

private:
    std::shared_ptr<BuilderContainer> firstVariableContainer;

    std::shared_ptr<BuilderContainer> secondVariableContainer;

    QString comboSelection;
};

#endif // CONDITIONAL_ELEMENT_H