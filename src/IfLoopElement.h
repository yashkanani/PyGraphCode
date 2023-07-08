#ifndef IF_LOOP_ELEMENT_H
#define IF_LOOP_ELEMENT_H

#include "AbstractElement.h"
class BuilderContainer;
class IfLoopElement : public AbstractElement {
public:
    IfLoopElement();
    std::shared_ptr<AbstractElement> clone() const override;
    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
    void setUserInput(std::shared_ptr<ElementUserInputs> userInput) override;
    std::shared_ptr<ElementUserInputs> getUserInput() override;


private:
    std::shared_ptr<BuilderContainer> conditionsContainer;
    std::shared_ptr<BuilderContainer> onTrueContainer;
    std::shared_ptr<BuilderContainer> onFalseContainer;
};

#endif // IF_LOOP_ELEMENT_H