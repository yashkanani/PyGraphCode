#ifndef CONDITIONAL_ELEMENT_H
#define CONDITIONAL_ELEMENT_H

#include "AbstractElement.h"

class BuilderContainer;
class QComboBox;
class ConditionalElement : public AbstractElement {
public:
    ConditionalElement();
    std::shared_ptr<AbstractElement> clone() const override;
    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;


private:
   

    BuilderContainer* firstVariableContainer;
    QComboBox* conditionComboBox;
    BuilderContainer* secondVariableContainer;
};

#endif // CONDITIONAL_ELEMENT_H