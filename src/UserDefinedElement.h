#ifndef USER_DEFINED_ELEMENT_H
#define USER_DEFINED_ELEMENT_H

#include "AbstractElement.h"
#include "BuilderContainer.h"

class UserDefinedElement : public AbstractElement {
public:
    UserDefinedElement();
    std::shared_ptr<AbstractElement> clone() const override;
    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
    void setUserInput(std::shared_ptr<ElementUserInputs> userInput) override;
    std::shared_ptr<ElementUserInputs> getUserInput() override;

private:
    std::shared_ptr<BuilderContainer> userContainer;
    bool isWidgetVisible;
};

#endif // USER_DEFINED_ELEMENT_H